// SearchMethodSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "SearchMethodSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchMethodSelDlg dialog


CSearchMethodSelDlg::CSearchMethodSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchMethodSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchMethodSelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSearchMethodSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchMethodSelDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchMethodSelDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchMethodSelDlg)
	ON_BN_CLICKED(IDC_METHOD1, OnMethod1)
	ON_BN_CLICKED(IDC_METHOD2, OnMethod2)
	ON_BN_CLICKED(IDC_METHOD3, OnMethod3)
	ON_BN_CLICKED(IDC_METHOD4, OnMethod4)
	ON_BN_CLICKED(IDC_METHOD5, OnMethod5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchMethodSelDlg message handlers

BOOL CSearchMethodSelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchMethodSelDlg::FullScreenMe()
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

void CSearchMethodSelDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_METHOD1)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_METHOD1)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_METHOD2)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_METHOD2)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_METHOD3)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_METHOD3)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_METHOD4)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_METHOD4)->SetWindowText(Arabize(sWindowText));	

	GetDlgItem(IDC_METHOD5)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_METHOD5)->SetWindowText(Arabize(sWindowText));	
	
}

void CSearchMethodSelDlg::OnMethod1() 
{
	m_iSelectedMethod=0;
	OnOK();
}

void CSearchMethodSelDlg::OnMethod2() 
{
	m_iSelectedMethod=1;
	OnOK();	
}

void CSearchMethodSelDlg::OnMethod3() 
{
	m_iSelectedMethod=2;
	OnOK();
}

void CSearchMethodSelDlg::OnMethod4() 
{
	m_iSelectedMethod=3;
	OnOK();		
}

void CSearchMethodSelDlg::OnMethod5() 
{
	m_iSelectedMethod=4;
	OnOK();		
}
