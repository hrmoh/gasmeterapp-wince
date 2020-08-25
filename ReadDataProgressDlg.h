#if !defined(AFX_READDATAPROGRESSDLG_H__97F9FA34_1224_43C0_8E2C_21F61D3A6AAC__INCLUDED_)
#define AFX_READDATAPROGRESSDLG_H__97F9FA34_1224_43C0_8E2C_21F61D3A6AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReadDataProgressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReadDataProgressDlg dialog

class CReadDataProgressDlg : public CDialog
{
// Construction
public:
	void ReadCONFIGDAT();
	void ReadCONTORDAT();
	CReadDataProgressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReadDataProgressDlg)
	enum { IDD = IDD_READPROGRESS };
	CProgressCtrl	m_ctlReadProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadDataProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReadDataProgressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READDATAPROGRESSDLG_H__97F9FA34_1224_43C0_8E2C_21F61D3A6AAC__INCLUDED_)
