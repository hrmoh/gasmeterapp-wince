#if !defined(AFX_ALERTBOXDLG_H__21590196_B464_4F9D_B16E_925E34EAB7F2__INCLUDED_)
#define AFX_ALERTBOXDLG_H__21590196_B464_4F9D_B16E_925E34EAB7F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlertBoxDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlertBoxDlg dialog

class CAlertBoxDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();
	CAlertBoxDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAlertBoxDlg)
	enum { IDD = IDD_ALERT };
	CString	m_sMyAlert;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlertBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAlertBoxDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALERTBOXDLG_H__21590196_B464_4F9D_B16E_925E34EAB7F2__INCLUDED_)
