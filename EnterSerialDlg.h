#if !defined(AFX_ENTERSERIALDLG_H__E18D1F4C_DD62_462F_974E_DB6F90FF3C21__INCLUDED_)
#define AFX_ENTERSERIALDLG_H__E18D1F4C_DD62_462F_974E_DB6F90FF3C21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnterSerialDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnterSerialDlg dialog

class CEnterSerialDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();

	CEnterSerialDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterSerialDlg)
	enum { IDD = IDD_GETSERIAL };
	CString	m_sSerialNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterSerialDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterSerialDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTERSERIALDLG_H__E18D1F4C_DD62_462F_974E_DB6F90FF3C21__INCLUDED_)
