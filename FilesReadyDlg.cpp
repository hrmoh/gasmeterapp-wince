// FilesReadyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "FilesReadyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilesReadyDlg dialog


CFilesReadyDlg::CFilesReadyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFilesReadyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilesReadyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFilesReadyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilesReadyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilesReadyDlg, CDialog)
	//{{AFX_MSG_MAP(CFilesReadyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilesReadyDlg message handlers

BOOL CFilesReadyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFilesReadyDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SADRTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SADRTITLE)->SetWindowText(Arabize(sWindowText));


}

void CFilesReadyDlg::FullScreenMe()
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
