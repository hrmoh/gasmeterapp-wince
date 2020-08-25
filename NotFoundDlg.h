#if !defined(AFX_NOTFOUNDDLG_H__5552B505_F6B4_443F_A85A_BEE5492EF1A5__INCLUDED_)
#define AFX_NOTFOUNDDLG_H__5552B505_F6B4_443F_A85A_BEE5492EF1A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NotFoundDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNotFoundDlg dialog

class CNotFoundDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();
	CNotFoundDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNotFoundDlg)
	enum { IDD = IDD_NOTFOUND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotFoundDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotFoundDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTFOUNDDLG_H__5552B505_F6B4_443F_A85A_BEE5492EF1A5__INCLUDED_)
