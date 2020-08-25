#if !defined(AFX_SEARCHMETHODSELDLG_H__79FA1634_C432_46CA_9867_ACA2975E009F__INCLUDED_)
#define AFX_SEARCHMETHODSELDLG_H__79FA1634_C432_46CA_9867_ACA2975E009F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchMethodSelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchMethodSelDlg dialog

class CSearchMethodSelDlg : public CDialog
{
// Construction
public:
	int m_iSelectedMethod;
	void PersianizeMe();
	void FullScreenMe();
	CSearchMethodSelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchMethodSelDlg)
	enum { IDD = IDD_SEARCH_SELTOOL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchMethodSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchMethodSelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMethod1();
	afx_msg void OnMethod2();
	afx_msg void OnMethod3();
	afx_msg void OnMethod4();
	afx_msg void OnMethod5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHMETHODSELDLG_H__79FA1634_C432_46CA_9867_ACA2975E009F__INCLUDED_)
