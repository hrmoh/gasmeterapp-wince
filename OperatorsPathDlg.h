#if !defined(AFX_OPERATORSPATHDLG_H__2259A5EE_38C6_485D_8321_B7DEDCB2438C__INCLUDED_)
#define AFX_OPERATORSPATHDLG_H__2259A5EE_38C6_485D_8321_B7DEDCB2438C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperatorsPathDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperatorsPathDlg dialog

class COperatorsPathDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();
	COperatorsPathDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COperatorsPathDlg)
	enum { IDD = IDD_OPERATOR_PASS };
	CString	m_sOpCode;
	CString	m_sPass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperatorsPathDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COperatorsPathDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATORSPATHDLG_H__2259A5EE_38C6_485D_8321_B7DEDCB2438C__INCLUDED_)
