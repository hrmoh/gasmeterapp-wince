#if !defined(AFX_READVALUEDLG_H__083FE7E1_7529_4ED5_BD24_1348BEC66B40__INCLUDED_)
#define AFX_READVALUEDLG_H__083FE7E1_7529_4ED5_BD24_1348BEC66B40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReadValueDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReadValueDlg dialog

class CReadValueDlg : public CDialog
{
// Construction
public:
	BOOL m_bReportMe;
	double m_fPrev;
	void FindMyCurrentCounter();
	CString m_sSubscriptionCode;
	void PersianizeMe();
	void FullScreenMe();
	CReadValueDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReadValueDlg)
	enum { IDD = IDD_CUSTOMERS_READ };
	CString	m_sPrevRead;
	CString	m_sPrevCounter;
	CString	m_sConsumption;
	CString	m_sNow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadValueDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReadValueDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDelete();
	afx_msg void OnError();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READVALUEDLG_H__083FE7E1_7529_4ED5_BD24_1348BEC66B40__INCLUDED_)
