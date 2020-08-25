#if !defined(AFX_MORESETTINGSDLG_H__5A239914_E1ED_434B_BC9C_CCBDD4A799E1__INCLUDED_)
#define AFX_MORESETTINGSDLG_H__5A239914_E1ED_434B_BC9C_CCBDD4A799E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoreSettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoreSettingsDlg dialog

class CMoreSettingsDlg : public CDialog
{
// Construction
public:
	void PersianizeMe();
	void FullScreenMe();
	CMoreSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMoreSettingsDlg)
	enum { IDD = IDD_MORESETTINGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoreSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMoreSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRestoreBackup();
	afx_msg void OnSetMainActive();
	afx_msg void OnSetAcActive();
	afx_msg void OnCopy2Ac();
	afx_msg void OnCopy2Main();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MORESETTINGSDLG_H__5A239914_E1ED_434B_BC9C_CCBDD4A799E1__INCLUDED_)
