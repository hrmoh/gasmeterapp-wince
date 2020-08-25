#if !defined(AFX_CUSTOMERSMOREINFODLG_H__CF7E1BF6_0C61_4D8A_B6B0_84400919FEBB__INCLUDED_)
#define AFX_CUSTOMERSMOREINFODLG_H__CF7E1BF6_0C61_4D8A_B6B0_84400919FEBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomersMoreinfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomersMoreinfoDlg dialog

class CCustomersMoreinfoDlg : public CDialog
{
// Construction
public:
	CString m_sSubscriptionCode;
	void FullScreenMe();
	void PersianizeMe();
	CCustomersMoreinfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomersMoreinfoDlg)
	enum { IDD = IDD_CUSTOMERS_MOREINFO };
	CString	m_sAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomersMoreinfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomersMoreinfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMERSMOREINFODLG_H__CF7E1BF6_0C61_4D8A_B6B0_84400919FEBB__INCLUDED_)
