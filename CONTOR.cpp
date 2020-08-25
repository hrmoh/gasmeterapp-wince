// CONTOR.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CONTOR.h"
#include "CONTORDlg.h"

#include "ado.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCONTORApp

BEGIN_MESSAGE_MAP(CCONTORApp, CWinApp)
	//{{AFX_MSG_MAP(CCONTORApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCONTORApp construction

CCONTORApp::CCONTORApp()
	: CWinApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCONTORApp object

CCONTORApp theApp;
CADODatabase	g_db;
BOOL g_bEnterUsingAd;
BOOL g_bEnterUsingSub;
BOOL g_bCheckPass;
CString g_sSettingsPath;
int g_iActiveOperator;
CString g_sLastReadSub;

/////////////////////////////////////////////////////////////////////////////
// CCONTORApp initialization

BOOL CCONTORApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	SetRegistryKey(_T("CONTOR"));

	g_bEnterUsingAd=(GetProfileInt(_T("Settings"), _T("EnterUsingAd"), 0)==1);
	g_bEnterUsingSub=(GetProfileInt(_T("Settings"), _T("EnterUsingSub"), 0)==1);
	g_bCheckPass=(GetProfileInt(_T("Settings"), _T("CheckPass"), 1)==1);
	g_sSettingsPath=GetProfileString(_T("Settings"), _T("SettingsPath"), _T("1384"));	
	g_sLastReadSub=GetProfileString(_T("Settings"), _T("LastRead"), _T(""));


	CCONTORDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
