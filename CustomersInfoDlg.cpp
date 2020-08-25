// CustomersInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "CustomersInfoDlg.h"

#include "ReportErrDlg.h"
#include "ReadValueDlg.h"
#include "CustomersMoreinfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomersInfoDlg dialog


CCustomersInfoDlg::CCustomersInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomersInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomersInfoDlg)
	m_sSubscriptionCode = _T("");
	m_sAD = _T("");
	m_sNam = _T("");
	m_sSer = _T("");
	//}}AFX_DATA_INIT
	m_bCanReadValue=TRUE;
}


void CCustomersInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomersInfoDlg)
	DDX_Text(pDX, IDC_SSUB, m_sSubscriptionCode);
	DDX_Text(pDX, IDC_SAD, m_sAD);
	DDX_Text(pDX, IDC_SNAM, m_sNam);
	DDX_Text(pDX, IDC_SSER, m_sSer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCustomersInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomersInfoDlg)
	ON_BN_CLICKED(IDC_ERR, OnErr)
	ON_BN_CLICKED(IDC_SELECT, OnSelect)
	ON_BN_CLICKED(IDC_MORE, OnMore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomersInfoDlg message handlers

BOOL CCustomersInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();


	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	GetDlgItem(IDC_SELECT)->EnableWindow(m_bCanReadValue);
	GetDlgItem(IDC_SSER)->ShowWindow(m_bCanReadValue);
	GetDlgItem(IDC_SSERTITLE)->ShowWindow(m_bCanReadValue);
	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustomersInfoDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDCANCEL)->GetWindowText(sWindowText);	
	GetDlgItem(IDCANCEL)->SetWindowText(Arabize(sWindowText));

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

	GetDlgItem(IDC_MORE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_MORE)->SetWindowText(Arabize(sWindowText));
	
	GetDlgItem(IDC_SELECT)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SELECT)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_ERR)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_ERR)->SetWindowText(Arabize(sWindowText));			

	GetDlgItem(IDC_SNAM)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SNAM)->SetWindowText(Arabize(sWindowText));			

	
}

void CCustomersInfoDlg::FullScreenMe()
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


void CCustomersInfoDlg::OnErr() 
{
	CReportErrDlg	dlg;
	dlg.m_sSubscriptionCode=m_sSubscriptionCode;
	dlg.m_bCanReadValue=m_bCanReadValue;
	dlg.DoModal();
	if(dlg.m_bReadMe)
		OnSelect();	
	else
		CDialog::OnOK();
}

void CCustomersInfoDlg::OnSelect() 
{
	CReadValueDlg dlg;
	dlg.m_sSubscriptionCode=m_sSubscriptionCode;
	dlg.m_sPrevRead=m_sPrevDate;	
	dlg.m_fPrev=m_fPrev;
	dlg.m_sPrevCounter.Format(_T("%.0f"), m_fPrev);	
	dlg.DoModal();
	if(dlg.m_bReportMe)
		OnErr();
	else
		CDialog::OnOK();
}

void CCustomersInfoDlg::OnMore() 
{
	CCustomersMoreinfoDlg	dlg;
	dlg.m_sAddress=m_sAddress;
	dlg.m_sSubscriptionCode=m_sSubscriptionCode;
	dlg.DoModal();	
}
