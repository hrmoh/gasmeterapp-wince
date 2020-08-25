#if !defined(AFX_QUESTIONBOXDLG_H__8EB5201D_DDE8_417E_A2BC_3B2F83FAF666__INCLUDED_)
#define AFX_QUESTIONBOXDLG_H__8EB5201D_DDE8_417E_A2BC_3B2F83FAF666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuestionBoxDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQuestionBoxDlg dialog

class CQuestionBoxDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();
	CQuestionBoxDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQuestionBoxDlg)
	enum { IDD = IDD_QUESTION };
	CString	m_sQuestion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuestionBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQuestionBoxDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUESTIONBOXDLG_H__8EB5201D_DDE8_417E_A2BC_3B2F83FAF666__INCLUDED_)
