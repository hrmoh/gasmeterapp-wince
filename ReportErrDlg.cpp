// ReportErrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "ReportErrDlg.h"
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
// CReportErrDlg dialog


CReportErrDlg::CReportErrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReportErrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportErrDlg)
	m_bErr1 = FALSE;
	m_bErr2 = FALSE;
	m_bErr3 = FALSE;
	m_bErr4 = FALSE;
	m_bErr5 = FALSE;
	//}}AFX_DATA_INIT	
	m_bCanReadValue=FALSE;
}


void CReportErrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportErrDlg)
	DDX_Check(pDX, IDC_CERR01, m_bErr1);
	DDX_Check(pDX, IDC_CERR02, m_bErr2);
	DDX_Check(pDX, IDC_CERR03, m_bErr3);
	DDX_Check(pDX, IDC_CERR04, m_bErr4);
	DDX_Check(pDX, IDC_CERR05, m_bErr5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportErrDlg, CDialog)
	//{{AFX_MSG_MAP(CReportErrDlg)
	ON_BN_CLICKED(IDC_NEXTPAGE, OnNextpage)
	ON_BN_CLICKED(IDC_PREVPAGE, OnPrevpage)
	ON_BN_CLICKED(IDC_READ, OnRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportErrDlg message handlers

void CReportErrDlg::FullScreenMe()
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

void CReportErrDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDCANCEL)->GetWindowText(sWindowText);	
	GetDlgItem(IDCANCEL)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_PREVPAGE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_PREVPAGE)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_NEXTPAGE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_NEXTPAGE)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_READ)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_READ)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_CERR01)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_CERR01)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_CERR02)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_CERR02)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_CERR03)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_CERR03)->SetWindowText(Arabize(sWindowText));		

	GetDlgItem(IDC_CERR04)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_CERR04)->SetWindowText(Arabize(sWindowText));		

	GetDlgItem(IDC_CERR05)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_CERR05)->SetWindowText(Arabize(sWindowText));		
	
}

BOOL CReportErrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	GetDlgItem(IDC_READ)->EnableWindow(m_bCanReadValue);

	LoadMyErrors();

	m_iPageNum=0;
	m_bReadMe=FALSE;
	ShowPage();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportErrDlg::OnNextpage() 
{
	SavePage();
	if(m_iPageNum<4)
		m_iPageNum++;
	else
		m_iPageNum=0;
	ShowPage();
}

void CReportErrDlg::OnPrevpage() 
{
	SavePage();
	if(m_iPageNum)
		m_iPageNum--;
	else
		m_iPageNum=4;	
	ShowPage();
}

void CReportErrDlg::ShowPage()
{
	CString sTemp;
	switch(m_iPageNum)
	{
	case 0:
		sTemp=_T("äÈæÏ ÈÑÓÈ ÈÇÑ˜ÏÏÇÑ");
		GetDlgItem(IDC_CERR01)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("äÈæÏ ÈÑÓÈ ÈÏæä ÈÇÑ˜Ï )ÏÑÈ ãäÒá(");
		GetDlgItem(IDC_CERR02)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÚÏã ÍÖæÑ ãÔÊÑ˜");
		GetDlgItem(IDC_CERR03)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÊÎáíå");
		GetDlgItem(IDC_CERR04)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ããÇäÚÊ");
		GetDlgItem(IDC_CERR05)->SetWindowText(Arabize(sTemp));	
		break;
	case 1:
		sTemp=_T("æÔíÏå");
		GetDlgItem(IDC_CERR01)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÈÑÏÇÔÊå");
		GetDlgItem(IDC_CERR02)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("˜ÏÑ");
		GetDlgItem(IDC_CERR03)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÓÑÞÊ ÇÒ");
		GetDlgItem(IDC_CERR04)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("äÔÊ ÇÒ");
		GetDlgItem(IDC_CERR05)->SetWindowText(Arabize(sTemp));	
		break;
	case 2:
		sTemp=_T("ÞØÚ ÇÒ");
		GetDlgItem(IDC_CERR01)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÌÇÈÌÇíí");
		GetDlgItem(IDC_CERR02)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("äæÓÇÒí");
		GetDlgItem(IDC_CERR03)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÎáÇÝ áæáå ˜Ôí");
		GetDlgItem(IDC_CERR04)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("˜äÊæÑ ÈÑÚ˜Ó");
		GetDlgItem(IDC_CERR05)->SetWindowText(Arabize(sTemp));	
		break;
	case 3:
		sTemp=_T("ÎÑÇÈí ÔãÇÑÔÑ");
		GetDlgItem(IDC_CERR01)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("äÏÇÔÊä áã");
		GetDlgItem(IDC_CERR02)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("Ô˜ÓÊí ˜äÊæÑ");
		GetDlgItem(IDC_CERR03)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("Ô˜ÓÊí ÔíÔå");
		GetDlgItem(IDC_CERR04)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÊÚæíÖ ˜äÊæÑ");
		GetDlgItem(IDC_CERR05)->SetWindowText(Arabize(sTemp));	
		break;
	case 4:
		sTemp=_T("ãÍá äÇãäÇÓÈ");
		GetDlgItem(IDC_CERR01)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÊÚãíÑÇÊ ÈäÇ");
		GetDlgItem(IDC_CERR02)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("ÏÓÊ˜ÇÑí ˜äÊæÑ");
		GetDlgItem(IDC_CERR03)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("˜äÊæÑ ãÔ˜æ˜");
		GetDlgItem(IDC_CERR04)->SetWindowText(Arabize(sTemp));	
		sTemp=_T("˜äÊæÑ ÏæÑÒÏå");
		GetDlgItem(IDC_CERR05)->SetWindowText(Arabize(sTemp));	
		break;
	}
	LoadPage();
}

void CReportErrDlg::SavePage()
{
	UpdateData();
	int iOffset=m_iPageNum*5;
	m_bErr1?(m_iErrors[iOffset++]=1):(m_iErrors[iOffset++]=0);
	m_bErr2?(m_iErrors[iOffset++]=1):(m_iErrors[iOffset++]=0);
	m_bErr3?(m_iErrors[iOffset++]=1):(m_iErrors[iOffset++]=0);
	m_bErr4?(m_iErrors[iOffset++]=1):(m_iErrors[iOffset++]=0);
	m_bErr5?(m_iErrors[iOffset++]=1):(m_iErrors[iOffset++]=0);
}

void CReportErrDlg::LoadPage()
{
	int iOffset=m_iPageNum*5;	
	m_bErr1=(m_iErrors[iOffset++]==1);
	m_bErr2=(m_iErrors[iOffset++]==1);
	m_bErr3=(m_iErrors[iOffset++]==1);
	m_bErr4=(m_iErrors[iOffset++]==1);
	m_bErr5=(m_iErrors[iOffset++]==1);
	UpdateData(FALSE);
}

void CReportErrDlg::LoadMyErrors()
{
	//bOk=g_db.Execute(_T("] ([SubscriptionCode] TEXT, [ErrorDate] TEXT, [ErrorTime] TEXT, [ErrorCode] SMALLINT, [WhoReports] INT)"));

	for(int i=0; i<25; i++)
		m_iErrors[i]=0;


	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("SELECT ErrorCode FROM OutputErrors WHERE SubscriptionCode='"+m_sSubscriptionCode+"';"), CADORecordset::openQuery);
	if(bOk)
	{
		while(!rs.IsEof())
		{
			int iError;
			rs.GetFieldValue(_T("ErrorCode"),		iError	);	
			m_iErrors[iError]=1;
			rs.MoveNext();
		}
	}
	rs.Close();

}

void CReportErrDlg::SaveMyErrors()
{
	SavePage();
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

	
	for(int i=0; i<25; i++)
	{
		CADORecordset rs=CADORecordset(&g_db);
		CString sError;
		sError.Format(_T("%d"), i);
		BOOL bOk=rs.Open(_T("SELECT ErrorCode FROM OutputErrors WHERE (SubscriptionCode='"+m_sSubscriptionCode+"') AND (ErrorCode="+sError+");"), CADORecordset::openQuery);
		if(bOk)
		{
			if(rs.IsEof())
			{
				if(m_iErrors[i]==1)
				{
					CADORecordset nrs=CADORecordset(&g_db);
					bOk = nrs.Open(_T("OutputErrors"), CADORecordset::openTable);
					nrs.AddNew();
					nrs.SetFieldValue(_T("SubscriptionCode"),		m_sSubscriptionCode	);		
					nrs.SetFieldValue(_T("ErrorCode"),		sError	);		
					nrs.SetFieldValue(_T("ErrorDate"),		sNowDate	);		
					nrs.SetFieldValue(_T("ErrorTime"),		sTime	);		
					nrs.SetFieldValue(_T("WhoReports"),		bWho	);		
					nrs.Update();
					nrs.Close();
					theApp.WriteProfileInt(_T("Settings"), _T("HasNotTransferedData"), 1);
				}
			}
			else
			{
				//previously saved
				CADORecordset urs=CADORecordset(&g_db);
				urs.Open(_T("SELECT * FROM OutputErrors WHERE (SubscriptionCode='"+m_sSubscriptionCode+"') AND (ErrorCode="+sError+");"), CADORecordset::openUpdate);

				if(m_iErrors[i]==1)
				{
					urs.Edit();
					urs.SetFieldValue(_T("ErrorCode"),		sError	);		
					urs.SetFieldValue(_T("ErrorDate"),		sNowDate	);		
					urs.SetFieldValue(_T("ErrorTime"),		sTime	);		
					urs.SetFieldValue(_T("WhoReports"),		bWho	);		
					urs.Update();
					theApp.WriteProfileInt(_T("Settings"), _T("HasNotTransferedData"), 1);
				}
				else
				{
					urs.Delete();
					theApp.WriteProfileInt(_T("Settings"), _T("HasNotTransferedData"), 1);
				}
					urs.Close();

			}
			rs.Close();
			g_sLastReadSub=m_sSubscriptionCode;
		}
	}
}

void CReportErrDlg::OnOK() 
{
	SaveMyErrors();
	CDialog::OnOK();
}

void CReportErrDlg::OnRead() 
{
	m_bReadMe=TRUE;
	CDialog::OnOK();
}
