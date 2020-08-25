#if !defined(AFX_SETTINGSDLG_H__DE1278F3_10A5_422C_A93B_E3E7131E8DA7__INCLUDED_)
#define AFX_SETTINGSDLG_H__DE1278F3_10A5_422C_A93B_E3E7131E8DA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg dialog

class CSettingsDlg : public CDialog
{
// Construction
public:
	BOOL m_bEnteredMeterReading;
	void FullScreenMe();
	void PersianizeMe();
	CSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsDlg)
	enum { IDD = IDD_CONTOR_SETTINGS };
	int		m_iGoTo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBackupnow4me();
	afx_msg void OnOthersettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__DE1278F3_10A5_422C_A93B_E3E7131E8DA7__INCLUDED_)
