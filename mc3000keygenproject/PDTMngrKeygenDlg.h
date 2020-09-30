// PDTMngrKeygenDlg.h : header file
//

#if !defined(AFX_PDTMNGRKEYGENDLG_H__7FDAED09_BFBB_4990_8A3F_6D600C717DB7__INCLUDED_)
#define AFX_PDTMNGRKEYGENDLG_H__7FDAED09_BFBB_4990_8A3F_6D600C717DB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPDTMngrKeygenDlg dialog

class CPDTMngrKeygenDlg : public CDialog
{
// Construction
public:
	CPDTMngrKeygenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPDTMngrKeygenDlg)
	enum { IDD = IDD_PDTMNGRKEYGEN_DIALOG };
	CButton	m_c3;
	CEdit	m_c2;
	CEdit	m_c1;
	CString	m_sPassword;
	CString	m_sHardwareKey;
	CString	m_sActivationCode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPDTMngrKeygenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPDTMngrKeygenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCon();
	afx_msg void OnCon2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PDTMNGRKEYGENDLG_H__7FDAED09_BFBB_4990_8A3F_6D600C717DB7__INCLUDED_)
