#if !defined(AFX_ADSEARCHDLG_H__C3EF6889_1A52_4ACE_8A77_EEFEDBDBAB10__INCLUDED_)
#define AFX_ADSEARCHDLG_H__C3EF6889_1A52_4ACE_8A77_EEFEDBDBAB10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ADSearchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CADSearchDlg dialog

class CADSearchDlg : public CDialog
{
// Construction
public:
	int m_iDoNext;
	void PersianizeMe();
	void FullScreenMe();
	CADSearchDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CADSearchDlg)
	enum { IDD = IDD_CUSTOMERS_SEARCHAD };
	CString	m_sSearch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADSearchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CADSearchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearch();
	afx_msg void OnChangemetheod();
	afx_msg void OnSettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADSEARCHDLG_H__C3EF6889_1A52_4ACE_8A77_EEFEDBDBAB10__INCLUDED_)
