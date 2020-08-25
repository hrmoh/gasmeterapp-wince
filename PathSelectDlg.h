#if !defined(AFX_PATHSELECTDLG_H__9D00418C_B6BE_4DBD_9D3C_0956830FF05A__INCLUDED_)
#define AFX_PATHSELECTDLG_H__9D00418C_B6BE_4DBD_9D3C_0956830FF05A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PathSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPathSelectDlg dialog

class CPathSelectDlg : public CDialog
{
// Construction
public:
	CString m_sLastAD;
	void FillCombo();
	void FullScreenMe();
	void PersianizeMe();
	CPathSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPathSelectDlg)
	enum { IDD = IDD_SELPATH };
	CComboBox	m_ctlPathCombo;
	int		m_iNowPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPathSelectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPathbegin();
	afx_msg void OnPathend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHSELECTDLG_H__9D00418C_B6BE_4DBD_9D3C_0956830FF05A__INCLUDED_)
