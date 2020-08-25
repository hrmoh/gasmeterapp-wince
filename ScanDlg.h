#if !defined(AFX_SCANDLG_H__E25D370F_B93B_44BD_9EFA_C1979BE048B2__INCLUDED_)
#define AFX_SCANDLG_H__E25D370F_B93B_44BD_9EFA_C1979BE048B2__INCLUDED_

#include <ScanCAPI.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanDlg.h : header file
//
// Define user messages
enum tagUSERMSGS
{
	UM_SCAN	= WM_USER + 0x200,
	UM_STARTSCANNING,
	UM_STOPSCANNING
};


/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog

class CScanDlg : public CDialog
{
// Construction
public:
	int m_iDoNext;
	void FullScreenMe();
	void PersianizeMe();
	void PrepareScanning();
	CScanDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_CUSTOMERS_SCAN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnScanDone();
	afx_msg void OnStopScan();
	virtual void OnOK();
	afx_msg void OnChangemetheod();
	afx_msg void OnSoftscan();
	afx_msg void OnSettings();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bStopScanning;
	LPSCAN_BUFFER m_lpScanBuffer;
	HANDLE m_hScanner;
	BOOL m_bTriggerFlag;
	BOOL m_bRequestPending;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANDLG_H__E25D370F_B93B_44BD_9EFA_C1979BE048B2__INCLUDED_)
