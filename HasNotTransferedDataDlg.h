#if !defined(AFX_HASNOTTRANSFEREDDATADLG_H__4AC9D822_529A_4826_B44E_B1D692785F7B__INCLUDED_)
#define AFX_HASNOTTRANSFEREDDATADLG_H__4AC9D822_529A_4826_B44E_B1D692785F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HasNotTransferedDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHasNotTransferedDataDlg dialog

class CHasNotTransferedDataDlg : public CDialog
{
// Construction
public:
	void FullScreenMe();
	void PersianizeMe();
	CHasNotTransferedDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHasNotTransferedDataDlg)
	enum { IDD = IDD_NOTTRANSFRED };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHasNotTransferedDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHasNotTransferedDataDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HASNOTTRANSFEREDDATADLG_H__4AC9D822_529A_4826_B44E_B1D692785F7B__INCLUDED_)
