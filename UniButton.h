//////////////////////////////////////////////////////////////////////
// UniButton.h
//////////////////////////////////////////////////////////////////////
// Copyright © 2005 Advatronix LLC
//
// With all inquiries please e-mail to:
// contact@advatronix.com
// or
// advatronix@yahoo.com
//////////////////////////////////////////////////////////////////////
// This code provided for non-commercial use only! As such it can be
// compiled and distributed in compiled form ONLY for "not for profit"
// applications ONLY!
//
// Re-distribution of the source code itself modified or unmodified is
// strictly prohibited without prior authorization!
//
// This code/software provided "AS IS" with no expressed or implied warranties.
// In no event should Advatronix LLC or its affiliates be liable for any
// direct, indirect, incidental, special, exemplary, or consequential
// damages of any kind, or any damages whatsoever, including, without
// limitation, those resulting from loss of use, data or profits,
// arising in any way out of the use of this software, even if
// advised of possibility of such damage.
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_UNIBUTTON_H__7CF75519_55DD_4B39_B0BE_710AAA9289C8__INCLUDED_)
#define AFX_UNIBUTTON_H__7CF75519_55DD_4B39_B0BE_710AAA9289C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//

/////////////////////////////////////////////////////////////////////////////
// CUniButton window

class CUniButton : public CButton
{
// Construction
public:
	CUniButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUniButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
#define		BTN_PUSHED_STATE	1
#define		BTN_RELEASED_STATE	0

//Functions
//------------------------------------------------------------
public:
	virtual			~CUniButton();
	void			SetTransparent(BOOL Enable = FALSE) {m_bTransparent = Enable;}
	void			SetTextColor(COLORREF TextColor = RGB(0,0,0));
	BOOL			FontStyle(CString sFont = "MS Sans Serif",  int iHeight = 10, int iWidth = 6, BOOL bFont3D = FALSE, BOOL bConcave = FALSE);
	inline void		HideText(BOOL bHide = TRUE) { m_bHideText = bHide; }
	inline void		SetBtnDownImg(int bmpID) { m_iBtnPushedBitmapID = bmpID; }
	inline void		SetBtnUpImg(int bmpID) { m_iBtnOffBitmapID = bmpID; }
	BOOL			LoadWAV(CString fileName, BOOL loadMEM);
	inline BOOL		WavIsSupported(void) { return m_bWavSupported;}
	BOOL			WAVLoaded(void);
	inline void		SetBkgndHandle(HBITMAP hBitmap) { m_hBmpBkgnd = hBitmap; }
	inline void		SetTopEdgeColor(COLORREF TopEdge = RGB(50,50,50)) {m_EdgeTop = TopEdge;}
	inline void		SetLeftEdgeColor(COLORREF LeftEdge = RGB(70,70,70)) {m_EdgeLeft = LeftEdge;}
	inline void		SetTranspColor(COLORREF transpCREF) { m_transpCREF = transpCREF; }

protected:
	void			PaintBckgnd(HDC h_destDC);
	void			PaintSunkenBckgnd(HDC h_destDC);
	void			PaintButton(HDC h_destDC);
	void			PaintText(HDC h_clientDC, CRect rect);
	BOOL			WAVSupported(void);
	BOOL			BtnPlay(void);
	void			Bkg2Bmp(void);


//Member Variables
//----------------------------------------------------
protected:
	int			m_iBtnPushedBitmapID;
	int			m_iBtnOffBitmapID;
	int			m_iState;
	BOOL		m_bTransparent;
	BOOL		m_bWavSupported;
	WAVEOUTCAPS	m_caps;
	CString		m_SoundFile;
	HANDLE		m_hFile;
	LPCSTR		m_lpWave;
	CFont		m_Font;
	BOOL		m_bFontCreated;
	BOOL		m_bFont3D;
	BOOL		m_bConcave;
	BOOL		m_bHideText;
	HBITMAP		m_hBmpBkgnd;  // Handle to Dialog Background Image
	COLORREF	m_TextColor;
	COLORREF	m_EdgeTop;
	COLORREF	m_EdgeLeft;
	COLORREF	m_transpCREF;

	// Generated message map functions
protected:
	//{{AFX_MSG(CUniButton)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIBUTTON_H__7CF75519_55DD_4B39_B0BE_710AAA9289C8__INCLUDED_)
