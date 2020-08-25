#if !defined(AFX_SEARCHSERIALDLG_H__FFEBB5DA_43AD_4A2F_A775_B55D7DD52CD1__INCLUDED_)
#define AFX_SEARCHSERIALDLG_H__FFEBB5DA_43AD_4A2F_A775_B55D7DD52CD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchSerialDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchSerialDlg dialog

class CSearchSerialDlg : public CDialog
{
// Construction
public:
	int m_iDoNext;
	void FullScreenMe();
	void PersianizeMe();
	CSearchSerialDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchSerialDlg)
	enum { IDD = IDD_CUSTOMERS_SEARCHSERIAL };
	CString	m_sSearch;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchSerialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchSerialDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSearch();
	afx_msg void OnChangemetheod();
	afx_msg void OnSettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHSERIALDLG_H__FFEBB5DA_43AD_4A2F_A775_B55D7DD52CD1__INCLUDED_)
