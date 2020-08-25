//////////////////////////////////////////////////////////////////////
// UniButton.cpp : implementation file
//
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

#include "stdafx.h"
#include "UniButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUniButton

CUniButton::CUniButton()
{
	m_iBtnPushedBitmapID	= 0;
	m_iBtnOffBitmapID		= 0;
	m_iState				= BTN_RELEASED_STATE;
	m_bTransparent			= FALSE;
	m_bWavSupported			= WAVSupported();
	m_SoundFile				= "";
	m_hFile					= INVALID_HANDLE_VALUE;
	m_lpWave				= NULL;
	m_bFontCreated			= FALSE;
	m_bFont3D				= FALSE;
	m_bConcave				= FALSE;
	m_bHideText				= TRUE;
	m_TextColor				= RGB(0,0,0);
	m_EdgeTop				= RGB(50,50,50);
	m_EdgeLeft				= RGB(70,70,70);
	m_transpCREF			= RGB(255,255,255);

}

CUniButton::~CUniButton()
{
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
	}

	if(m_lpWave != NULL)
	{
		free((void*)m_lpWave);
		m_lpWave = NULL;
	}

	if(m_bFontCreated)
	{
		m_Font.DeleteObject();
	}
}


BEGIN_MESSAGE_MAP(CUniButton, CButton)
	//{{AFX_MSG_MAP(CUniButton)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUniButton message handlers


//------------------------------------------------------------------
//
//------------------------------------------------------------------
void CUniButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item

	CString sCaption;
	HDC		h_clientDC;
	CRect	rect;
	CDC		*pDC;

	h_clientDC	= lpDrawItemStruct->hDC;
	pDC			= CDC::FromHandle(lpDrawItemStruct->hDC);
	GetWindowText(sCaption);
	rect		= lpDrawItemStruct->rcItem;
	
	pDC->SetBkMode(TRANSPARENT);
	switch(m_iState)
	{
		case(BTN_PUSHED_STATE):
		{
			if(m_bTransparent)
			{
				PaintSunkenBckgnd(lpDrawItemStruct->hDC);
			}
			else
			{
				PaintBckgnd(lpDrawItemStruct->hDC);
				PaintButton(lpDrawItemStruct->hDC);
			}
			break;
		}

		case(BTN_RELEASED_STATE):
		{
			if(m_bTransparent)
			{
				PaintBckgnd(lpDrawItemStruct->hDC);
			}
			else
			{
				PaintBckgnd(lpDrawItemStruct->hDC);
				PaintButton(lpDrawItemStruct->hDC);
			}
			break;
		}
	}

	if(m_bHideText == FALSE)
	{
		PaintText(h_clientDC, rect);
	}

}


//*******************************************************************************
// Copy Background to Button Face
//*******************************************************************************
//------------------------------------------------------------------
//
//------------------------------------------------------------------
void CUniButton::PaintBckgnd(HDC h_destDC)
{
	
	CWnd *	pParent;
	CRect	wndRect;
	int		width;
	int		height;
	int		srcx;
	int		srcy;
	//BITMAP	bmp;

	//::GetObject(m_hBmpBkgnd, sizeof(bmp), &bmp);
	HDC hDC = ::CreateCompatibleDC(NULL);
	::SelectObject(hDC, m_hBmpBkgnd);

	pParent = this->GetParent();
	GetWindowRect(&wndRect);
	pParent->ScreenToClient(&wndRect);

	width = wndRect.Width();
	height = wndRect.Height();
	srcx = wndRect.left;
	srcy = wndRect.top;

	::BitBlt(h_destDC, 0, 0, width, height, hDC, srcx, srcy, SRCCOPY);
	
	::DeleteDC(hDC);
}

//------------------------------------------------------------------
// This function paints the background shifted 2 pixels right and
// down. It also draws top and left edge.
//------------------------------------------------------------------
void CUniButton::PaintSunkenBckgnd(HDC h_destDC)
{
	CWnd *		pParent;
	CDC	*		pParentCDC;
	CRect		wndRect;
	int			width;
	int			height;
	BYTE		rValue=0;
	BYTE		gValue=0;
	BYTE		bValue=0;

	//BITMAP bmp;

	//::GetObject(m_hBmpBkgnd, sizeof(bmp), &bmp);
	HDC hDC = ::CreateCompatibleDC(NULL);
	::SelectObject(hDC, m_hBmpBkgnd);

	pParent = this->GetParent();
	GetWindowRect(&wndRect);
	pParent->ScreenToClient(&wndRect);

	width = wndRect.Width();
	height = wndRect.Height();

	pParentCDC = pParent->GetWindowDC();

	::BitBlt(h_destDC, 2, 2, width-2, height-2, hDC, wndRect.left, wndRect.top, SRCCOPY);
	::DeleteDC(hDC);

	
	CDC *pDC = CDC::FromHandle(h_destDC);
	pDC->Draw3dRect(0, 0, wndRect.Width(), 2, m_EdgeTop, m_EdgeTop);
	pDC->Draw3dRect(0, 1, 2, wndRect.Height(), m_EdgeLeft, m_EdgeLeft);

}


//------------------------------------------------------------------
//
//------------------------------------------------------------------
void CUniButton::PaintButton(HDC h_destDC)
{
	CRect		cltRect;
	BITMAP		bmp;
	HBITMAP		hBmp;
	HDC			hDC;
	//COLORREF	transpCREF;

	// Return if no bitmap assigned
	//--------------------------------------
	if(m_iBtnOffBitmapID == 0 || m_iBtnPushedBitmapID == 0)
	{
		return;
	}

	//transpCREF = RGB(255,255,255);

	GetClientRect(&cltRect);
	switch(m_iState)
	{
		case(BTN_PUSHED_STATE):
		{
			hBmp = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(m_iBtnPushedBitmapID));
			break;
		}

		case(BTN_RELEASED_STATE):
		{
			hBmp = ::LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(m_iBtnOffBitmapID));
			break;
		}
	}
	::GetObject(hBmp, sizeof(bmp), &bmp);
	hDC = ::CreateCompatibleDC(NULL);
	SelectObject(hDC, hBmp);
	::TransparentImage(h_destDC, 0, 0, cltRect.Width(), cltRect.Height(), hDC, 0, 0, cltRect.Width(), cltRect.Height(), m_transpCREF);
	::DeleteObject(hBmp);
	::DeleteDC(hDC);
}



//------------------------------------------------------------------
// This function paints text over the button - plain or 3D
//------------------------------------------------------------------
void CUniButton::PaintText(HDC h_clientDC, CRect rect)
{
	CFont*		def_font;
	CString		sCaption;
	CDC *pDC = CDC::FromHandle(h_clientDC);
	
	GetWindowText(sCaption);

	if(m_bFontCreated)
	{
		def_font = pDC->SelectObject(&m_Font);
	}

	pDC->SetBkMode(TRANSPARENT);

	if(m_bFont3D)
	{
		if(m_bConcave)
		{
			pDC->SetTextColor(RGB(255,255,255));
			pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
			pDC->SetTextColor(m_TextColor);
			rect.left = rect.left - 1;
			rect.top = rect.top - 1;
			rect.bottom = rect.bottom - 1;
			rect.right = rect.right - 1;
			pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		
		}
		else
		{
			pDC->SetTextColor(RGB(255,255,255));
			pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
			pDC->SetTextColor(m_TextColor);
			rect.left = rect.left + 1;
			rect.top = rect.top + 1;
			rect.bottom = rect.bottom + 1;
			rect.right = rect.right + 1;
			pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		
		}
	}
	else
	{
		pDC->SetTextColor(m_TextColor);
		pDC->DrawText(sCaption, rect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	}

	if(m_bFontCreated)
	{
		pDC->SelectObject(def_font);
	}
}



//******************************************************************
// Font Setup
//******************************************************************
//------------------------------------------------------------------
//
//------------------------------------------------------------------
BOOL CUniButton::FontStyle(CString sFont, int iHeight, int iWidth, BOOL bFont3D, BOOL bConcave)
{
	
	if(m_bFontCreated)
	{
		m_Font.DeleteObject();
	}

	if(0 != m_Font.CreateFont(iHeight, iWidth, 0, 0, 
					FW_BOLD, //FW_NORMAL, 
					0, 0, 0, 0, 0, 0, 0,0, sFont))
	{
		m_bFontCreated		= TRUE;
		m_bFont3D = bFont3D;
		m_bConcave = bConcave;
		return	TRUE;
	}
	else
	{
		m_bFontCreated		= FALSE;
		return FALSE;
	}
}

//------------------------------------------------------------------
//
//------------------------------------------------------------------
void CUniButton::SetTextColor(COLORREF TextColor)
{
	m_TextColor = TextColor;
	return;
}

//******************************************************************
// WAV related functions
//******************************************************************
//------------------------------------------------------------------
//
//------------------------------------------------------------------
BOOL	CUniButton::WAVSupported(void)
{
	if(waveOutGetDevCaps(WAVE_MAPPER, &m_caps, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR)
	{
		if(m_caps.dwFormats & WAVE_FORMAT_1M08)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}

//------------------------------------------------------------------
//
//------------------------------------------------------------------
BOOL	CUniButton::LoadWAV(CString fileName, BOOL loadMEM)
{
	DWORD	dwSize;
	DWORD	dwBytesRead;
	BOOL	bResult;

	// No support - no load
	//-------------------------------------------
	if(m_bWavSupported == FALSE)
	{
		return FALSE;
	}

	// Get rid of previous assignments if any
	//-------------------------------------------
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
	}

	if(m_lpWave != NULL)
	{
		free((void*)m_lpWave);
		m_lpWave = NULL;
	}

	// Open file
	//--------------------------------------------
	m_SoundFile = fileName;

	m_hFile = CreateFile(	m_SoundFile,
							GENERIC_READ|GENERIC_WRITE,
							FILE_SHARE_READ,
							NULL,
							OPEN_ALWAYS,//OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL
							);

	if(m_hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	//Load file into memory if requested
	//----------------------------------------
	if(loadMEM)
	{
		// Get file size
		dwSize = GetFileSize(m_hFile, NULL);
		if(dwSize == 0xFFFFFFFF)
		{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			return FALSE;
		}

		// Allocate memory for it
		//---------------------------------
		m_lpWave = (LPCSTR)malloc(dwSize);
		if(m_lpWave == NULL)
		{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			return FALSE;
		}

		// Load into memory
		//---------------------------------
		bResult = ReadFile(m_hFile, (void *)m_lpWave, dwSize, &dwBytesRead, NULL);
		if((bResult == FALSE)||(dwBytesRead != dwSize))
		{
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			free((void*)m_lpWave);
			m_lpWave = NULL;
			return FALSE;
		}

		// Get rid of the file
		//-------------------------------------
		CloseHandle(m_hFile);
		m_hFile = INVALID_HANDLE_VALUE;
		return TRUE;
	}
	else
	{
		return TRUE;
	}
	
return	TRUE;
}


//------------------------------------------------------------------
//
//------------------------------------------------------------------
BOOL	CUniButton::BtnPlay(void)
{
	// Play from buffer
	//-------------------------------------
	if(m_lpWave != NULL)
	{
		sndPlaySound((unsigned short *)m_lpWave, SND_MEMORY|SND_ASYNC);
		return TRUE;
	}

	// Play from file
	//--------------------------------------
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
		sndPlaySound(m_SoundFile, SND_ASYNC);
		return TRUE;
	}

	return FALSE;
}


//------------------------------------------------------------------
//
//------------------------------------------------------------------
BOOL	CUniButton::WAVLoaded(void)
{
	if((m_lpWave != NULL)||(m_hFile != INVALID_HANDLE_VALUE))
	{
		return TRUE;
	}
	return FALSE;
}


//******************************************************************
// Button Message Handlers
//******************************************************************
//------------------------------------------------------------------
//
//------------------------------------------------------------------
void CUniButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_iState = BTN_RELEASED_STATE;
	//Invalidate();
	
	//Default();
	CButton::OnLButtonUp(nFlags, point);
}

//------------------------------------------------------------------
//
//------------------------------------------------------------------
void CUniButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_iState = BTN_PUSHED_STATE;
	//Invalidate();
	if(WAVLoaded())
	{
		BtnPlay();
	}
	
	Default();
	//CButton::OnLButtonDown(nFlags, point);
}
