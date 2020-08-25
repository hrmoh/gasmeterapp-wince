#if !defined(AFX_WRITEDATAPROGRESSDLG_H__7755A60E_1921_4D73_85D7_B8E7F49CC611__INCLUDED_)
#define AFX_WRITEDATAPROGRESSDLG_H__7755A60E_1921_4D73_85D7_B8E7F49CC611__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WriteDataProgressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWriteDataProgressDlg dialog

class CWriteDataProgressDlg : public CDialog
{
// Construction
public:
	void WriteERRORSDAT();
	void WriteOUTPUTDAT();
	CWriteDataProgressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWriteDataProgressDlg)
	enum { IDD = IDD_WRITEPROGRESS };
	CProgressCtrl	m_ctlWriteProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWriteDataProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWriteDataProgressDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WRITEDATAPROGRESSDLG_H__7755A60E_1921_4D73_85D7_B8E7F49CC611__INCLUDED_)
