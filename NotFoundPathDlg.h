#if !defined(AFX_NOTFOUNDPATHDLG_H__D62E4EF5_EBC0_4228_8BF2_900383757468__INCLUDED_)
#define AFX_NOTFOUNDPATHDLG_H__D62E4EF5_EBC0_4228_8BF2_900383757468__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NotFoundPathDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNotFoundPathDlg dialog

class CNotFoundPathDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();
	CNotFoundPathDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNotFoundPathDlg)
	enum { IDD = IDD_NOTFOUNDPATH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotFoundPathDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotFoundPathDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTFOUNDPATHDLG_H__D62E4EF5_EBC0_4228_8BF2_900383757468__INCLUDED_)
