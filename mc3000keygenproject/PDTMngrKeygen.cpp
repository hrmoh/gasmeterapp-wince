// PDTMngrKeygen.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PDTMngrKeygen.h"
#include "PDTMngrKeygenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDTMngrKeygenApp

BEGIN_MESSAGE_MAP(CPDTMngrKeygenApp, CWinApp)
	//{{AFX_MSG_MAP(CPDTMngrKeygenApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPDTMngrKeygenApp construction

CPDTMngrKeygenApp::CPDTMngrKeygenApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPDTMngrKeygenApp object

CPDTMngrKeygenApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPDTMngrKeygenApp initialization

BOOL CPDTMngrKeygenApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CPDTMngrKeygenDlg dlg;
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
