#if !defined(AFX_FILESREADYDLG_H__E8C198E7_6C71_43AC_AE6A_4F9F0BE2E438__INCLUDED_)
#define AFX_FILESREADYDLG_H__E8C198E7_6C71_43AC_AE6A_4F9F0BE2E438__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilesReadyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilesReadyDlg dialog

class CFilesReadyDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();
	CFilesReadyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilesReadyDlg)
	enum { IDD = IDD_FILESREADY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesReadyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilesReadyDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESREADYDLG_H__E8C198E7_6C71_43AC_AE6A_4F9F0BE2E438__INCLUDED_)
