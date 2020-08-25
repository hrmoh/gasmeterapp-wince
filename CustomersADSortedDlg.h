#if !defined(AFX_CUSTOMERSADSORTEDDLG_H__94B5B3DB_6DA0_4867_89A8_B3459C0B8516__INCLUDED_)
#define AFX_CUSTOMERSADSORTEDDLG_H__94B5B3DB_6DA0_4867_89A8_B3459C0B8516__INCLUDED_

#include "ado.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomersADSortedDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomersADSortedDlg dialog

class CCustomersADSortedDlg : public CDialog
{
// Construction
public:
	int m_iDoNext;
	void CloseWhiteList();
	void ShowCurrent();
	void OpenWhiteList();
	void PersianizeMe();
	void FullScreenMe();
	CCustomersADSortedDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomersADSortedDlg)
	enum { IDD = IDD_CUSTOMERS_ADSORTED };
	CString	m_sSubscriptionCode;
	CString	m_sAD;
	CString	m_sNam;
	CString	m_sSer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomersADSortedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomersADSortedDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnNext();
	afx_msg void OnPrev();
	afx_msg void OnSelect();
	afx_msg void OnMore();
	afx_msg void OnErr();
	afx_msg void OnChangemetheod();
	afx_msg void OnSettings();
	afx_msg void OnSelpath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CADORecordset m_rs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMERSADSORTEDDLG_H__94B5B3DB_6DA0_4867_89A8_B3459C0B8516__INCLUDED_)
