#if !defined(AFX_CUSTOMERSINFODLG_H__C7679B91_DACA_4027_9EDE_2D154C4C012E__INCLUDED_)
#define AFX_CUSTOMERSINFODLG_H__C7679B91_DACA_4027_9EDE_2D154C4C012E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomersInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomersInfoDlg dialog

class CCustomersInfoDlg : public CDialog
{
// Construction
public:
	BOOL m_bCanReadValue;
	double m_fPrev;
	CString m_sPrevDate;
	CString m_sAddress;
	void FullScreenMe();
	void PersianizeMe();
	CCustomersInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomersInfoDlg)
	enum { IDD = IDD_CUSTOMERS_INFO };
	CString	m_sSubscriptionCode;
	CString	m_sAD;
	CString	m_sNam;
	CString	m_sSer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomersInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomersInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnErr();
	afx_msg void OnSelect();
	afx_msg void OnMore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMERSINFODLG_H__C7679B91_DACA_4027_9EDE_2D154C4C012E__INCLUDED_)
