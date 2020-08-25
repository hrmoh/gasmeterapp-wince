#if !defined(AFX_SEARCHSUBDLG_H__AB2F7030_F596_4671_A08C_B2EA00B5DDD1__INCLUDED_)
#define AFX_SEARCHSUBDLG_H__AB2F7030_F596_4671_A08C_B2EA00B5DDD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchSubDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchSubDlg dialog

class CSearchSubDlg : public CDialog
{
// Construction
public:
	int m_iDoNext;
	void PersianizeMe();
	void FullScreenMe();
	CSearchSubDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchSubDlg)
	enum { IDD = IDD_CUSTOMERS_SEARCHSUB };
	CString	m_sSearch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchSubDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchSubDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearch();
	afx_msg void OnChangemetheod();
	afx_msg void OnSettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHSUBDLG_H__AB2F7030_F596_4671_A08C_B2EA00B5DDD1__INCLUDED_)
