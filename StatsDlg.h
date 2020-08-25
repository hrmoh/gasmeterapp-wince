#if !defined(AFX_STATSDLG_H__789FB395_D937_4700_9AB3_C261FC934626__INCLUDED_)
#define AFX_STATSDLG_H__789FB395_D937_4700_9AB3_C261FC934626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatsDlg dialog

class CStatsDlg : public CDialog
{
// Construction
public:
	void ComputeToday();
	void ComputeNotRead();
	void FullScreenMe();
	void PersianizeMe();
	CStatsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatsDlg)
	enum { IDD = IDD_CUSTOMERS_STATS };
	CString	m_sTodayDate;
	CString	m_sTotal;
	CString	m_sNotRead;
	CString	m_sTodayStats;
	CString	m_sFileDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatsDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_iTotal;
	void ComputeTotal();
	void ComputeTodayDate();
	void LoadStats();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATSDLG_H__789FB395_D937_4700_9AB3_C261FC934626__INCLUDED_)
