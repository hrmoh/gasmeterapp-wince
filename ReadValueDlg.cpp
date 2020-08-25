// ReadValueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "ReadValueDlg.h"

#include "ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CADODatabase	g_db;
extern int g_iActiveOperator;
extern CString g_sLastReadSub;
extern CCONTORApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CReadValueDlg dialog


CReadValueDlg::CReadValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadValueDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadValueDlg)
	m_sPrevRead = _T("");
	m_sPrevCounter = _T("");
	m_sConsumption = _T("");
	m_sNow = _T("");
	//}}AFX_DATA_INIT
}


void CReadValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadValueDlg)
	DDX_Text(pDX, IDC_SPREVD, m_sPrevRead);
	DDX_Text(pDX, IDC_SPREVC, m_sPrevCounter);
	DDX_Text(pDX, IDC_SCON, m_sConsumption);
	DDX_Text(pDX, IDC_ENOW, m_sNow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadValueDlg, CDialog)
	//{{AFX_MSG_MAP(CReadValueDlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_ERROR, OnError)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadValueDlg message handlers

void CReadValueDlg::FullScreenMe()
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

void CReadValueDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_ERROR)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_ERROR)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDCANCEL)->GetWindowText(sWindowText);	
	GetDlgItem(IDCANCEL)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_SPREVDTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SPREVDTITLE)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_SPREVCTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SPREVCTITLE)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_SNOWTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SNOWTITLE)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_SCONTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SCONTITLE)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_DELETE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_DELETE)->SetWindowText(Arabize(sWindowText));		
}

BOOL CReadValueDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	m_bReportMe=FALSE;

	FindMyCurrentCounter();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReadValueDlg::FindMyCurrentCounter()
{
	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("SELECT CurrentCounter FROM DeviceOutput WHERE SubscriptionCode='"+m_sSubscriptionCode+"';"), CADORecordset::openQuery);
	if(bOk)
	{
		if(!rs.IsEof())
		{
			double fNow;
			rs.GetFieldValue(_T("CurrentCounter"),		fNow	);	
			m_sNow.Format(_T("%.0f"), fNow);	
			double fConsumption=fNow-m_fPrev;
			m_sConsumption.Format(_T("%.0f"), fConsumption);	
			UpdateData(FALSE);
		}
	}
	rs.Close();
}

void CReadValueDlg::OnOK() 
{
	//[CurrentDate] ?
	//[RDate] TEXT, [RTime] TEXT, [CurrentDate] TEXT, [WhoReports] INT)"));
	UpdateData();

	if(m_sNow.GetLength()==0)
		CDialog::OnOK();
	else
	{

	theApp.WriteProfileInt(_T("Settings"), _T("HasNotTransferedData"), 1);
	//date
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

	//time
	CString sTime;
	sTime.Format(_T("%.2d%.2d%.2d"),systime.wHour, systime.wMinute, systime.wSecond);

	//operator;
	BYTE bWho=g_iActiveOperator;


	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("SELECT CurrentCounter FROM DeviceOutput WHERE SubscriptionCode='"+m_sSubscriptionCode+"';"), CADORecordset::openQuery);
	if(bOk)
	{
		if(rs.IsEof())
		{
			//new
			CADORecordset nrs=CADORecordset(&g_db);
			bOk = nrs.Open(_T("DeviceOutput"), CADORecordset::openTable);
			nrs.AddNew();
			nrs.SetFieldValue(_T("SubscriptionCode"),		m_sSubscriptionCode	);		
			nrs.SetFieldValue(_T("CurrentCounter"),		m_sNow	);		
			nrs.SetFieldValue(_T("RDate"),		sNowDate	);		
			nrs.SetFieldValue(_T("RTime"),		sTime	);		
			nrs.SetFieldValue(_T("WhoReports"),		bWho	);		
			nrs.Update();
			nrs.Close();

		}
		else
		{
			//update
			CADORecordset urs=CADORecordset(&g_db);
			urs.Open(_T("SELECT * FROM DeviceOutput WHERE SubscriptionCode='"+m_sSubscriptionCode+"';"), CADORecordset::openUpdate);
			urs.Edit();
			urs.SetFieldValue(_T("CurrentCounter"),		m_sNow	);		
			urs.SetFieldValue(_T("RDate"),		sNowDate	);		
			urs.SetFieldValue(_T("RTime"),		sTime	);		
			urs.SetFieldValue(_T("WhoReports"),		bWho	);		
			urs.Update();
			urs.Close();

		}
	}
	rs.Close();

	g_sLastReadSub=m_sSubscriptionCode;

	CDialog::OnOK();
	}
}

void CReadValueDlg::OnDelete() 
{
	if(g_db.Execute(_T("DELETE FROM DeviceOutput WHERE SubscriptionCode='"+m_sSubscriptionCode+"';")))
	{
		m_sNow=_T("");
		m_sConsumption=_T("");
		UpdateData(FALSE);
	}	
}

void CReadValueDlg::OnError() 
{
	m_bReportMe=TRUE;
	CDialog::OnOK();
}
