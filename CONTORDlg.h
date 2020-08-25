// CONTORDlg.h : header file
//

#if !defined(AFX_CONTORDLG_H__A2B9B876_7A4B_4074_8283_E1F50FCEC291__INCLUDED_)
#define AFX_CONTORDLG_H__A2B9B876_7A4B_4074_8283_E1F50FCEC291__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "UniButton.h"

/////////////////////////////////////////////////////////////////////////////
// CCONTORDlg dialog

class CCONTORDlg : public CDialog
{
// Construction
public:
	void OpenDatabase();
	CString GetBatteryLifePercent();
	BOOL CheckOperator(CString sOpCode, CString sPass);
	void PersianizeMe();
	void FullScreenMe();
	CCONTORDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCONTORDlg)
	enum { IDD = IDD_CONTOR_DIALOG };
	CUniButton	m_btnShowInfo;
	CUniButton	m_btnClose;
	CUniButton	m_btnMeterReading;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCONTORDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HBITMAP m_hBmpBkgnd;
	CFont m_Font;

	// Generated message map functions
	//{{AFX_MSG(CCONTORDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMeterreading();
	afx_msg void OnPaint();
	afx_msg void OnShowinformaton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bEnteredMeterReading;
//	DWORD GetESN(LPELECTRONIC_SERIAL_NUMBER lpESN);
	BOOL VerifySoftwareKey();
	BOOL m_bIsOnFirstPage;
	int m_iSearchMethod;
	UINT m_uPrepareMsg;
	UINT m_uGenFilesMsg;
	UINT m_uDataTransfered;

	CString ComputeTodayDate();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTORDLG_H__A2B9B876_7A4B_4074_8283_E1F50FCEC291__INCLUDED_)
