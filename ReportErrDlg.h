#if !defined(AFX_REPORTERRDLG_H__0A060C38_0CA3_49E0_B2D6_6EE74B4685E2__INCLUDED_)
#define AFX_REPORTERRDLG_H__0A060C38_0CA3_49E0_B2D6_6EE74B4685E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportErrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportErrDlg dialog

class CReportErrDlg : public CDialog
{
// Construction
public:
	BOOL m_bCanReadValue;
	BOOL m_bReadMe;
	void SaveMyErrors();
	void LoadMyErrors();
	void LoadPage();
	void SavePage();
	CString m_sSubscriptionCode;
	void PersianizeMe();
	void FullScreenMe();
	CReportErrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportErrDlg)
	enum { IDD = IDD_CUSTOMERS_ERROR };
	BOOL	m_bErr1;
	BOOL	m_bErr2;
	BOOL	m_bErr3;
	BOOL	m_bErr4;
	BOOL	m_bErr5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportErrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportErrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNextpage();
	afx_msg void OnPrevpage();
	virtual void OnOK();
	afx_msg void OnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_iErrors[25];
	void ShowPage();
	int m_iPageNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTERRDLG_H__0A060C38_0CA3_49E0_B2D6_6EE74B4685E2__INCLUDED_)
