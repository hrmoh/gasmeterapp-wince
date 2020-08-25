// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "SettingsDlg.h"
#include "ado.h"
#include "AlertBoxDlg.h"
#include "SettingsPassDlg.h"
#include "MoreSettingsDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog
extern CCONTORApp theApp;


CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDlg)
	m_iGoTo = -1;
	//}}AFX_DATA_INIT
}


void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDlg)
	DDX_Radio(pDX, IDC_RGOTO, m_iGoTo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingsDlg)
	ON_BN_CLICKED(IDC_BACKUPNOW4ME, OnBackupnow4me)
	ON_BN_CLICKED(IDC_OTHERSETTINGS, OnOthersettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg message handlers

BOOL CSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	if(m_bEnteredMeterReading)
	{
		GetDlgItem(IDC_BACKUPNOW4ME)->EnableWindow(FALSE);
		GetDlgItem(IDC_OTHERSETTINGS)->EnableWindow(FALSE);
	}

	m_iGoTo=theApp.GetProfileInt(_T("Settings"), _T("AfterRead"), 2);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingsDlg::FullScreenMe()
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

void CSettingsDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_RGOTO)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_RGOTO)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_RGOTO2)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_RGOTO2)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_RGOTO3)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_RGOTO3)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_BACKUPNOW4ME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_BACKUPNOW4ME)->SetWindowText(Arabize(sWindowText));
	
	GetDlgItem(IDC_OTHERSETTINGS)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_OTHERSETTINGS)->SetWindowText(Arabize(sWindowText));

}

void CSettingsDlg::OnOK() 
{
	UpdateData();
	theApp.WriteProfileInt(_T("Settings"), _T("AfterRead"), m_iGoTo);	
	CDialog::OnOK();
}

void CSettingsDlg::OnBackupnow4me() 
{

	CString sDefaultStorage=_T("\\contor.cdb");
	if(theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==1)
	{
		sDefaultStorage=_T("\\Storage Card\\contor.cdb");
	}
	CAlertBoxDlg adlg;
	if(CopyFile(sDefaultStorage, _T("\\Application\\contor\\contor.cbk"), FALSE))
	{
		adlg.m_sMyAlert=_T("Å‘ Ì»«‰ »« „Ê›ﬁÌ   ÂÌÂ ‘œ.");
	}
	else
	{
		adlg.m_sMyAlert=_T("Œÿ« œ—  ÂÌÂ Å‘ Ì»«‰!");
	}
	adlg.DoModal();

}	

void CSettingsDlg::OnOthersettings() 
{
	CSettingsPassDlg	sdlg;
	if(sdlg.DoModal()==IDOK)
	{
		if(theApp.GetProfileString(_T("Settings"), _T("SettingsPath"), _T(""))!=sdlg.m_sPass)
		{
			CAlertBoxDlg adlg;
			adlg.m_sMyAlert=_T("ò·„Â ⁄»Ê— «‘ »«Â «” .");
			adlg.DoModal();
		}		
		else
		{
			CMoreSettingsDlg dlg;
			dlg.DoModal();
		}
	}
}
