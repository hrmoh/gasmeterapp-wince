// StatsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "StatsDlg.h"
#include "PersianSupport.h"
#include "ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CADODatabase	g_db;
extern CCONTORApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStatsDlg dialog


CStatsDlg::CStatsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatsDlg)
	m_sTodayDate = _T("");
	m_sTotal = _T("");
	m_sNotRead = _T("");
	m_sTodayStats = _T("");
	m_sFileDate = _T("");
	//}}AFX_DATA_INIT
	m_iTotal=0;
}


void CStatsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatsDlg)
	DDX_Text(pDX, IDC_SDATE, m_sTodayDate);
	DDX_Text(pDX, IDC_SSTAT, m_sTotal);
	DDX_Text(pDX, IDC_SNOTREAD, m_sNotRead);
	DDX_Text(pDX, IDC_STODAY, m_sTodayStats);
	DDX_Text(pDX, IDC_SFDATE, m_sFileDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatsDlg, CDialog)
	//{{AFX_MSG_MAP(CStatsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatsDlg message handlers

void CStatsDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SSUBTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SSUBTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SSUBTITLE2)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SSUBTITLE2)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SNAMTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SNAMTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SADTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SADTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SSERTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SSERTITLE)->SetWindowText(Arabize(sWindowText));
}

void CStatsDlg::FullScreenMe()
{
	CRect rect;

	CRect* lpRect=&rect;


	// Get size fo desktop area
	SystemParametersInfo(SPI_GETWORKAREA,0,(PVOID)lpRect,0);

#ifdef WIN32_PLATFORM_PSPC

	{
		typedef HRESULT (WINAPI *SHSIPINFOFUNC)(UINT uiAction,
												UINT uiParam,
												PVOID pvParam,
												UINT fWinIni);
		HINSTANCE hDll;
		SIPINFO si;

		// Try and load the Palm-Sized PC / PocketPC shell dll
		hDll = LoadLibrary(TEXT("aygshell.dll"));

		// If DLL was loaded
		if ( hDll != NULL )
		{
			SHSIPINFOFUNC lpfnSHSipInfo;

			// Try and get the address of the SHSipInfo function
			lpfnSHSipInfo = (SHSIPINFOFUNC)GetProcAddress(hDll,(PVOID)TEXT("SHSipInfo"));

			// If the function was found
			if ( lpfnSHSipInfo != NULL )
			{
				HRESULT hResult;
				
				// Initialize the SIPINFO structure
				memset(&si,0,sizeof(si));
				si.cbSize = sizeof(si);
				
				// Call the function
				hResult = (*lpfnSHSipInfo)(SPI_GETSIPINFO,0,(PVOID)&si,0);
				
				if ( hResult )
				{
					// Replace system work area with visble area not covered by SIP
					*lpRect = si.rcVisibleDesktop;
					
#ifdef WIN32_PLATFORM_POCKETPC

					// If SIP is NOT showing on PocketPC, then account for menu bar
					if ( ! ( si.fdwFlags & 1 ) )
					{
						lpRect->bottom -= 26;
					}

#endif
				}
			}
		}

		// Free the DLL
		FreeLibrary(hDll);
	}

#endif



	MoveWindow(&rect);
}

BOOL CStatsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	LoadStats();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStatsDlg::LoadStats()
{
	m_sFileDate=theApp.GetProfileString(_T("Settings"), _T("FileDate"), _T("00/00/00"));
	ComputeTodayDate();
	ComputeTotal();
	ComputeNotRead();
	ComputeToday();
	UpdateData(FALSE);
}

void CStatsDlg::ComputeTodayDate()
{
	CString sNowDate;
	SYSTEMTIME systime;
	int		m_JD;
	int		m_JM;
	int		m_JY;
	int		m_GD;
	int		m_GM;
	int		m_GY;

	GetLocalTime(&systime);
	m_GD = systime.wDay-1;
	m_GM = systime.wMonth-1;
	m_GY = systime.wYear;
	gregorian_to_jalali(&m_JY, &m_JM, &m_JD, m_GY, m_GM+1, m_GD+1);


	CString sTemp;
	sTemp.Format(_T("%4.d"), m_JY);
	sNowDate=CString(sTemp[2])+sTemp[3];
	sNowDate=sNowDate+_T("/");
	sTemp.Format(_T("%.2d"), m_JM);
	sNowDate=sNowDate+sTemp;
	sNowDate=sNowDate+_T("/");
	sTemp.Format(_T("%.2d"), m_JD);
	sNowDate=sNowDate+sTemp;	
	m_sTodayDate=sNowDate;
}

void CStatsDlg::ComputeTotal()
{
	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("WhiteList"), CADORecordset::openTable);
	if(!bOk)
		OnOK();
	if(!rs.IsEof())
	{
		m_sTotal.Format(_T("%d"), rs.GetRecordCount());
		m_iTotal=rs.GetRecordCount();
	}
	else
		m_sTotal=_T("0");
	rs.Close();
}

void CStatsDlg::ComputeNotRead()
{
	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("DeviceOutput"), CADORecordset::openTable);
	if(!bOk)
		OnOK();
	if(!rs.IsEof())
	{
		m_sNotRead.Format(_T("%d"), m_iTotal-rs.GetRecordCount());
	}
	else
		m_sNotRead.Format(_T("%d"), m_iTotal);
	rs.Close();
}

void CStatsDlg::ComputeToday()
{
	CString sNowDate;
	SYSTEMTIME systime;
	int		m_JD;
	int		m_JM;
	int		m_JY;
	int		m_GD;
	int		m_GM;
	int		m_GY;

	GetLocalTime(&systime);
	m_GD = systime.wDay-1;
	m_GM = systime.wMonth-1;
	m_GY = systime.wYear;
	gregorian_to_jalali(&m_JY, &m_JM, &m_JD, m_GY, m_GM+1, m_GD+1);


	CString sTemp;
	sTemp.Format(_T("%4.d"), m_JY);
	sNowDate=CString(sTemp[2])+sTemp[3];
	sTemp.Format(_T("%.2d"), m_JM);
	sNowDate=sNowDate+sTemp;
	sTemp.Format(_T("%.2d"), m_JD);
	sNowDate=sNowDate+sTemp;	

	CADORecordset rs=CADORecordset(&g_db);
	CString sQuery=_T("SELECT * FROM DeviceOutput WHERE RDate='")+sNowDate+_T("'");
	BOOL bOk=rs.Open(sQuery, CADORecordset::openQuery);
	if(!bOk)
		OnOK();
	if(!rs.IsEof())
	{
		m_sTodayStats.Format(_T("%d"), rs.GetRecordCount());
	}
	else
		m_sTodayStats.Format(_T("%d"), 0);
	rs.Close();
}
