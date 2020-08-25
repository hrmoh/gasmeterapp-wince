// MoreSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "MoreSettingsDlg.h"
#include "QuestionBoxDlg.h"
#include "ado.h"
#include "AlertBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCONTORApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CMoreSettingsDlg dialog


CMoreSettingsDlg::CMoreSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMoreSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMoreSettingsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMoreSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoreSettingsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMoreSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CMoreSettingsDlg)
	ON_BN_CLICKED(IDC_METHOD1, OnRestoreBackup)
	ON_BN_CLICKED(IDC_METHOD2, OnSetMainActive)
	ON_BN_CLICKED(IDC_METHOD3, OnSetAcActive)
	ON_BN_CLICKED(IDC_METHOD4, OnCopy2Ac)
	ON_BN_CLICKED(IDC_METHOD5, OnCopy2Main)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoreSettingsDlg message handlers

BOOL CMoreSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	GetDlgItem(IDC_METHOD2)->EnableWindow((theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==1));
	GetDlgItem(IDC_METHOD3)->EnableWindow((theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==0));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMoreSettingsDlg::FullScreenMe()
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

void CMoreSettingsDlg::PersianizeMe()
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

void CMoreSettingsDlg::OnRestoreBackup() 
{
	CQuestionBoxDlg qdlg;
	qdlg.m_sQuestion=_T("İÇíá ÔÊíÈÇä ÌÇíÒíä İÇíá ÌÇÑí ÔæÏ¿");
	if(qdlg.DoModal()==IDOK)
	{
	CString sDefaultStorage=_T("\\contor.cdb");
	if(theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==1)
	{
		sDefaultStorage=_T("\\Storage Card\\contor.cdb");
	}
	CAlertBoxDlg adlg;
	if(CopyFile(_T("\\Application\\contor\\contor.cbk"), sDefaultStorage, FALSE))
	{
		adlg.m_sMyAlert=_T("ÔÊíÈÇä ÈÇ ãæİŞíÊ ÈÇÒÑÏÇäÏå ÔÏ.");
	}
	else
	{
		adlg.m_sMyAlert=_T("ÎØÇ ÏÑ ÈÇÒÔÊ ÔÊíÈÇä");
	}
	adlg.DoModal();


	}
}

void CMoreSettingsDlg::OnSetMainActive() 
{
	if(theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==1)
	{
		theApp.WriteProfileInt(_T("Settings"), _T("Storage"), 0);

	}	
	CAlertBoxDlg adlg;
	adlg.m_sMyAlert=_T("ÇØáÇÚÇÊ ÈÑ Ñæí ÍÇİÙå ÇÕáí ĞÎíÑå ãí ÔæÏ.");
	adlg.DoModal();
	GetDlgItem(IDC_METHOD2)->EnableWindow((theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==1));
	GetDlgItem(IDC_METHOD3)->EnableWindow((theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==0));
}

void CMoreSettingsDlg::OnSetAcActive() 
{
	if(theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==0)
	{
		theApp.WriteProfileInt(_T("Settings"), _T("Storage"), 1);

	}	
	CAlertBoxDlg adlg;
	adlg.m_sMyAlert=_T("ÇØáÇÚÇÊ ÈÑ Ñæí ˜ÇÑÊ ÍÇİÙå ĞÎíÑå ãí ÔæÏ.");
	adlg.DoModal();	
	GetDlgItem(IDC_METHOD2)->EnableWindow((theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==1));
	GetDlgItem(IDC_METHOD3)->EnableWindow((theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==0));
}

void CMoreSettingsDlg::OnCopy2Ac() 
{
	CQuestionBoxDlg qdlg;
	qdlg.m_sQuestion=_T("ÇØáÇÚÇÊ ˜ÇÑÊ ÍÇİÙå ÌÇíÒíä ÔæÏ¿");
	if(qdlg.DoModal()!=IDOK) return;

	CAlertBoxDlg adlg;
	if(CopyFile(_T("\\contor.cdb"), _T("\\Storage Card\\contor.cdb"), FALSE))
	{
		adlg.m_sMyAlert=_T("ÇØáÇÚÇÊ Èå ˜ÇÑÊ ÍÇİÙå ˜í ÔÏ.");
	}
	else
	{
		adlg.m_sMyAlert=_T("ÎØÇ ÏÑ ˜í Èå ˜ÇÑÊ");
	}
	adlg.DoModal();	

}

void CMoreSettingsDlg::OnCopy2Main() 
{
	CQuestionBoxDlg qdlg;
	qdlg.m_sQuestion=_T("ÇØáÇÚÇÊ ÍÇİÙå ÇÕáí ÌÇíÒíä ÔæÏ¿");
	if(qdlg.DoModal()!=IDOK) return;

	CAlertBoxDlg adlg;
	if(CopyFile(_T("\\Storage Card\\contor.cdb"), _T("\\contor.cdb"), FALSE))
	{
		adlg.m_sMyAlert=_T("ÇØááÇÚÇÊ Èå ÍÇİÙå ÇÕáí ˜í ÔÏ.");
	}
	else
	{
		adlg.m_sMyAlert=_T("ÎØÇ ÏÑ ˜í Èå ÍÇİÙå ÇÕáí");
	}
	adlg.DoModal();		
}
