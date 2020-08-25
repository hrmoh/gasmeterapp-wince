// CONTOR.h : main header file for the CONTOR application
//

#if !defined(AFX_CONTOR_H__72A3CCF8_0829_46E6_BF80_B3F27B767917__INCLUDED_)
#define AFX_CONTOR_H__72A3CCF8_0829_46E6_BF80_B3F27B767917__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "PersianSupport.h"

/////////////////////////////////////////////////////////////////////////////
// CCONTORApp:
// See CONTOR.cpp for the implementation of this class
//

class CCONTORApp : public CWinApp
{
public:
	CCONTORApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCONTORApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCONTORApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTOR_H__72A3CCF8_0829_46E6_BF80_B3F27B767917__INCLUDED_)
