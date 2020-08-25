#if !defined(AFX_SETTINGSPASSDLG_H__EBD44A93_C0B1_43C1_BA26_9C2B09C6D618__INCLUDED_)
#define AFX_SETTINGSPASSDLG_H__EBD44A93_C0B1_43C1_BA26_9C2B09C6D618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsPassDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingsPassDlg dialog

class CSettingsPassDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();
	CSettingsPassDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsPassDlg)
	enum { IDD = IDD_SETTINGS_PASS };
	CString	m_sPass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsPassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsPassDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSPASSDLG_H__EBD44A93_C0B1_43C1_BA26_9C2B09C6D618__INCLUDED_)
