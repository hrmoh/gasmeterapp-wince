// CustomersADSortedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "CustomersADSortedDlg.h"
#include "CustomersMoreinfoDlg.h"
#include "ReadValueDlg.h"
#include "ReportErrDlg.h"
#include "SearchMethodSelDlg.h"
#include "NotFoundDlg.h"
#include "StatsDlg.h"
#include "PathSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_bEnterUsingAd;
extern CString g_sLastReadSub;
extern CCONTORApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CCustomersADSortedDlg dialog

extern CADODatabase	g_db;


CCustomersADSortedDlg::CCustomersADSortedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomersADSortedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomersADSortedDlg)
	m_sSubscriptionCode = _T("");
	m_sAD = _T("");
	m_sNam = _T("");
	m_sSer = _T("");
	//}}AFX_DATA_INIT
}


void CCustomersADSortedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomersADSortedDlg)
	DDX_Text(pDX, IDC_SSUB, m_sSubscriptionCode);
	DDX_Text(pDX, IDC_SAD, m_sAD);
	DDX_Text(pDX, IDC_SNAM, m_sNam);
	DDX_Text(pDX, IDC_SSER, m_sSer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomersADSortedDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomersADSortedDlg)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_MORE, OnMore)
	ON_BN_CLICKED(IDC_ERR, OnErr)
	ON_BN_CLICKED(IDC_CHANGEMETHEOD, OnChangemetheod)
	ON_BN_CLICKED(IDC_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_SELPATH, OnSelpath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomersADSortedDlg message handlers

void CCustomersADSortedDlg::FullScreenMe()
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

BOOL CCustomersADSortedDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_iDoNext=-1;
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	if(!g_bEnterUsingAd)
	{
		GetDlgItem(IDC_SELECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SSER)->ShowWindow(FALSE);
		GetDlgItem(IDC_SSERTITLE)->ShowWindow(FALSE);
	}

	OpenWhiteList();

	ShowCurrent();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomersADSortedDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SSUBTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SSUBTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SNAMTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SNAMTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SADTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SADTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SSERTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SSERTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_NEXT)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_NEXT)->SetWindowText(Arabize(sWindowText));
	
	GetDlgItem(IDC_PREV)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_PREV)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_MORE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_MORE)->SetWindowText(Arabize(sWindowText));
	
	GetDlgItem(IDC_SELECT)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SELECT)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_CHANGEMETHEOD)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_CHANGEMETHEOD)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SETTINGS)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SETTINGS)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_ERR)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_ERR)->SetWindowText(Arabize(sWindowText));			

	GetDlgItem(IDC_SELPATH)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SELPATH)->SetWindowText(Arabize(sWindowText));				
}

void CCustomersADSortedDlg::OpenWhiteList()
{
	m_rs=CADORecordset(&g_db);
	BOOL bOk=m_rs.Open(_T("SELECT * FROM WhiteList ORDER BY AddressCode;"), CADORecordset::openQuery);
	if(!bOk)
		OnOK();
	if(m_rs.IsEof())
	{
		CNotFoundDlg dlg;
		dlg.DoModal();
		OnOK();
	}
	if(g_sLastReadSub.GetLength()!=0)
	{		
		CADORecordset rs=CADORecordset(&g_db);
		rs.Open(_T("SELECT * FROM WhiteList WHERE SubscriptionCode='"+g_sLastReadSub+"' ORDER BY AddressCode;"), CADORecordset::openQuery);
		if(!rs.IsEof())
		{
			int iOrder;
			rs.GetFieldValue(_T("AOrder"), iOrder);
			m_rs.SetAbsolutePosition(iOrder);
		}
		rs.Close();
	}

}

void CCustomersADSortedDlg::ShowCurrent()
{
	m_rs.GetFieldValue(_T("SubscriptionCode"),		m_sSubscriptionCode	);	
	CString sNam;
	m_rs.GetFieldValue(_T("FName"),		sNam	);
	m_rs.GetFieldValue(_T("FLName"),		m_sNam	);	
	m_sNam=sNam+" "+m_sNam;
	m_sNam=Arabize(m_sNam);
	m_rs.GetFieldValue(_T("CounterSerial"),		m_sSer	);	
	m_rs.GetFieldValue(_T("AddressCode"),		m_sAD	);	
	UpdateData(FALSE);

}

void CCustomersADSortedDlg::CloseWhiteList()
{
	m_rs.Close();
}

void CCustomersADSortedDlg::OnOK() 
{
	m_rs.GetFieldValue(_T("SubscriptionCode"),		g_sLastReadSub	);		
	CloseWhiteList();	
	CDialog::OnOK();
}

void CCustomersADSortedDlg::OnNext() 
{
	m_rs.MoveNext();
	if(m_rs.IsEof())
		m_rs.MoveLast();
	ShowCurrent();
}

void CCustomersADSortedDlg::OnPrev() 
{
	m_rs.MovePrevious();
	if(m_rs.IsBof())
		m_rs.MoveFirst();
	ShowCurrent();	
}

void CCustomersADSortedDlg::OnSelect() 
{
	CReadValueDlg dlg;
	m_rs.GetFieldValue(_T("SubscriptionCode"),		dlg.m_sSubscriptionCode	);
	CString sPrevDate;
	m_rs.GetFieldValue(_T("PrevDate"),		sPrevDate	);
	dlg.m_sPrevRead=CString(sPrevDate[0])+sPrevDate[1]+"/"+sPrevDate[2]+sPrevDate[3]+"/"+sPrevDate[4]+sPrevDate[5];	
	m_rs.GetFieldValue(_T("PrevCounter"),		dlg.m_fPrev	);
	dlg.m_sPrevCounter.Format(_T("%.0f"), dlg.m_fPrev);	
	dlg.DoModal();
	if(dlg.m_bReportMe)
		OnErr();
	else
	{
		switch(theApp.GetProfileInt(_T("Settings"), _T("AfterRead"), 2))
		{
		case 0:
			OnNext();
			break;
		case 1:
			OnPrev();
			break;
		}
	}
}

void CCustomersADSortedDlg::OnMore() 
{
	CCustomersMoreinfoDlg	dlg;
	m_rs.GetFieldValue(_T("Address"),		dlg.m_sAddress	);
	m_rs.GetFieldValue(_T("SubscriptionCode"),		dlg.m_sSubscriptionCode	);
	dlg.DoModal();
}	

void CCustomersADSortedDlg::OnErr() 
{
	CReportErrDlg	dlg;
	dlg.m_bCanReadValue=g_bEnterUsingAd;
	m_rs.GetFieldValue(_T("SubscriptionCode"),		dlg.m_sSubscriptionCode	);
	dlg.DoModal();
	if(dlg.m_bReadMe)
		OnSelect();
}

void CCustomersADSortedDlg::OnChangemetheod() 
{
	CSearchMethodSelDlg	dlg;
	dlg.m_iSelectedMethod=4;
	dlg.DoModal();
	if(dlg.m_iSelectedMethod!=4)
	{
		m_iDoNext=dlg.m_iSelectedMethod;
		OnOK();
	}
}

void CCustomersADSortedDlg::OnSettings() 
{
	CStatsDlg	dlg;
	dlg.DoModal();
}

void CCustomersADSortedDlg::OnSelpath() 
{
	CPathSelectDlg	dlg;
	dlg.m_sLastAD=m_sAD;
	dlg.DoModal();

	if(g_sLastReadSub.GetLength()!=0)
	{		
		CADORecordset rs=CADORecordset(&g_db);
		rs.Open(_T("SELECT * FROM WhiteList WHERE SubscriptionCode='"+g_sLastReadSub+"' ORDER BY AddressCode;"), CADORecordset::openQuery);
		if(!rs.IsEof())
		{
			int iOrder;
			rs.GetFieldValue(_T("AOrder"), iOrder);
			m_rs.SetAbsolutePosition(iOrder);
		}
		rs.Close();
		ShowCurrent();
	}
}
