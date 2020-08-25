// CONTORDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "CONTORDlg.h"

#include "ReadDataProgressDlg.h"
#include "CustomersADSortedDlg.h"
#include "ScanDlg.h"
#include "SearchSerialDlg.h"
#include "SearchSubDlg.h"
#include "ADSearchDlg.h"
#include "OperatorsPathDlg.h"
#include "WriteDataProgressDlg.h"
#include "HasNotTransferedDataDlg.h"
#include "SettingsDlg.h"
#include "EnterSerialDlg.h"
#include "AlertBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




extern CCONTORApp theApp;
extern CADODatabase	g_db;
extern BOOL g_bCheckPass;
extern int g_iActiveOperator;
extern CString g_sLastReadSub;

// This version only works with RCM2Api32
#ifndef PLAT_RCM2API32
#define PLAT_RCM2API32
#endif

#include <RcmCAPI.h>

typedef DWORD (WINAPI* LPFNRCMGETESN)(LPELECTRONIC_SERIAL_NUMBER lpESN);

//----------------------------------------------------------------------------
//
//  FUNCTION:   GetESN(LPELECTRONIC_SERIAL_NUMBER lpESN)
//
//  PURPOSE:    Get the electronic serial number if available 
//
//  PARAMETERS:
//      lpESN - pointer to the buffer receives the ESN
//
//  RETURN VALUE:
//      DWORD flag specifies whether or not the function succeeded.
//
//----------------------------------------------------------------------------
DWORD GetESN(LPELECTRONIC_SERIAL_NUMBER lpESN)
{
	HANDLE hLib = NULL;
	LPFNRCMGETESN lpfnRCM_GetESN = NULL;
	DWORD dwResult = 0;
	
	// Open RCM2 library and attempt to gain access to GetESN function
	hLib = LoadLibrary(L"rcm2api32.dll");
	if(NULL == hLib)
	{
		return 0;
	}

	lpfnRCM_GetESN = (LPFNRCMGETESN)GetProcAddress((HMODULE )hLib,L"RCM_GetESN");
	if(NULL == lpfnRCM_GetESN)
	{
		FreeLibrary((HMODULE)hLib);
		return 0;
	}

	dwResult = lpfnRCM_GetESN(lpESN);
	if(E_RCM_SUCCESS != dwResult)
	{
		FreeLibrary((HMODULE)hLib);
		return 0;
	}


	FreeLibrary((HMODULE)hLib);
	return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CCONTORDlg dialog

CCONTORDlg::CCONTORDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCONTORDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCONTORDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iSearchMethod=theApp.GetProfileInt(_T("Settings"), _T("LastSearchMethod"), 4);
	m_bIsOnFirstPage=TRUE;
	m_hBmpBkgnd = NULL;
	m_bEnteredMeterReading=FALSE;
}

void CCONTORDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCONTORDlg)
	DDX_Control(pDX, IDC_SHOWINFORMATON, m_btnShowInfo);
	DDX_Control(pDX, IDOK, m_btnClose);
	DDX_Control(pDX, IDC_METERREADING, m_btnMeterReading);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCONTORDlg, CDialog)
	//{{AFX_MSG_MAP(CCONTORDlg)
	ON_BN_CLICKED(IDC_METERREADING, OnMeterreading)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SHOWINFORMATON, OnShowinformaton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCONTORDlg message handlers

BOOL CCONTORDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	while(!VerifySoftwareKey())
	{
		CEnterSerialDlg sdlg;
		if(sdlg.DoModal()==IDCANCEL)
		{
			PostQuitMessage(0);
			return FALSE;
		}
	}
	if(!VerifySoftwareKey())
		{
			PostQuitMessage(0);
			return FALSE;
		}
	m_uPrepareMsg=RegisterWindowMessage(_T("um_quitcontor"));
	m_uGenFilesMsg=RegisterWindowMessage(_T("um_genfiles"));	
	m_uDataTransfered=RegisterWindowMessage(_T("um_datatransfered"));

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	FullScreenMe();
	CenterWindow(GetDesktopWindow());	// center to the hpc screen
	PersianizeMe();

	m_Font.CreateFont(20, 10, 0, 0,
					FW_NORMAL, 
					0, 0, 0, 0, 0, 0, 0,0, _T("B Sina"));

	m_hBmpBkgnd = ::LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_BKGND) );

	m_btnMeterReading.SetWindowPos(this,15,50,288,30,SWP_NOZORDER);
	m_btnMeterReading.SetBtnUpImg(IDB_METERBITMAP);
	m_btnMeterReading.SetBtnDownImg(IDB_METERBITMAPD);
	m_btnMeterReading.SetBkgndHandle(m_hBmpBkgnd);
	m_btnMeterReading.HideText(FALSE);
	m_btnMeterReading.SetTransparent(FALSE);
	m_btnMeterReading.SetTranspColor(RGB(0,0,255));	
	m_btnMeterReading.SetTextColor(RGB(0,0,0));
	//m_btnMeterReading.FontStyle("B Titr", 14, 8, TRUE, FALSE);

	m_btnShowInfo.SetWindowPos(this,15,82,288,30,SWP_NOZORDER);
	m_btnShowInfo.SetBtnUpImg(IDB_METERBITMAP);
	m_btnShowInfo.SetBtnDownImg(IDB_METERBITMAPD);
	m_btnShowInfo.SetBkgndHandle(m_hBmpBkgnd);
	m_btnShowInfo.HideText(FALSE);
	m_btnShowInfo.SetTransparent(FALSE);
	m_btnShowInfo.SetTranspColor(RGB(0,0,255));	
	m_btnShowInfo.SetTextColor(RGB(0,0,0));


	m_btnClose.SetWindowPos(this,3,3,24,24,SWP_NOZORDER);
	m_btnClose.SetBtnUpImg(IDB_BITMAP_CLOSE);
	m_btnClose.SetBtnDownImg(IDB_BITMAP_CLOSED);
	m_btnClose.SetBkgndHandle(m_hBmpBkgnd);
	m_btnClose.SetTransparent(FALSE);
	m_btnClose.SetTranspColor(RGB(0,0,255));	

	

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CCONTORDlg::FullScreenMe()
{
	CRect rect;

	CRect* lpRect=&rect;


	// Get size fo desktop area
	SystemParametersInfo(SPI_GETWORKAREA,0,(PVOID)lpRect,0);

#ifdef WIN32_PLATFORM_PSPC

	{
		typedef HRESULT (WINAPI *SHSIPINFOFUNC)(UINT uiAction,
												UINT uiParam,
												PVOID pvParam,
												UINT fWinIni);
		HINSTANCE hDll;
		SIPINFO si;

		// Try and load the Palm-Sized PC / PocketPC shell dll
		hDll = LoadLibrary(TEXT("aygshell.dll"));

		// If DLL was loaded
		if ( hDll != NULL )
		{
			SHSIPINFOFUNC lpfnSHSipInfo;

			// Try and get the address of the SHSipInfo function
			lpfnSHSipInfo = (SHSIPINFOFUNC)GetProcAddress(hDll,(PVOID)TEXT("SHSipInfo"));

			// If the function was found
			if ( lpfnSHSipInfo != NULL )
			{
				HRESULT hResult;
				
				// Initialize the SIPINFO structure
				memset(&si,0,sizeof(si));
				si.cbSize = sizeof(si);
				
				// Call the function
				hResult = (*lpfnSHSipInfo)(SPI_GETSIPINFO,0,(PVOID)&si,0);
				
				if ( hResult )
				{
					// Replace system work area with visble area not covered by SIP
					*lpRect = si.rcVisibleDesktop;
					
#ifdef WIN32_PLATFORM_POCKETPC

					// If SIP is NOT showing on PocketPC, then account for menu bar
					if ( ! ( si.fdwFlags & 1 ) )
					{
						lpRect->bottom -= 26;
					}

#endif
				}
			}
		}

		// Free the DLL
		FreeLibrary(hDll);
	}

#endif



	MoveWindow(&rect);
}

void CCONTORDlg::PersianizeMe()
{
	CString sWindowText;
//	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
//	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SHOWINFORMATON)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SHOWINFORMATON)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_METERREADING)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_METERREADING)->SetWindowText(Arabize(sWindowText));

}

void CCONTORDlg::OnMeterreading() 
{
	OpenDatabase();
	g_iActiveOperator=1;
	if(g_bCheckPass)
	{
		COperatorsPathDlg passdlg;
		if(passdlg.DoModal()!=IDOK) return;
		if(!CheckOperator(passdlg.m_sOpCode, passdlg.m_sPass))
			return;
	}
	m_iSearchMethod=theApp.GetProfileInt(_T("Settings"), _T("LastSearchMethod"), 4);
	m_bIsOnFirstPage=FALSE;
	BOOL bEndIt=FALSE;
	do
	{
	if(m_iSearchMethod==4)
	{
		CCustomersADSortedDlg dlg;
		dlg.DoModal();
		if(dlg.m_iDoNext!=-1)
		{
			m_iSearchMethod=dlg.m_iDoNext;
		}
		else
			bEndIt=TRUE;
	}
	else
	if(m_iSearchMethod==0)
	{
		CScanDlg dlg;
		dlg.DoModal();
		if(dlg.m_iDoNext!=-1)
		{
			m_iSearchMethod=dlg.m_iDoNext;
		}
		else
			bEndIt=TRUE;
	}
	else
	if(m_iSearchMethod==1)
	{
		CSearchSerialDlg dlg;
		dlg.DoModal();
		if(dlg.m_iDoNext!=-1)
		{
			m_iSearchMethod=dlg.m_iDoNext;
		}
		else
			bEndIt=TRUE;
	}
	else
	if(m_iSearchMethod==2)
	{
		CSearchSubDlg dlg;
		dlg.DoModal();
		if(dlg.m_iDoNext!=-1)
		{
			m_iSearchMethod=dlg.m_iDoNext;
		}
		else
			bEndIt=TRUE;
	}
	else
	if(m_iSearchMethod==3)
	{
		CADSearchDlg dlg;
		dlg.DoModal();
		if(dlg.m_iDoNext!=-1)
		{
			m_iSearchMethod=dlg.m_iDoNext;
		}
		else
			bEndIt=TRUE;
	}	

	}while(!bEndIt);
	theApp.WriteProfileInt(_T("Settings"), _T("LastSearchMethod"), m_iSearchMethod);
	m_bIsOnFirstPage=TRUE;
	if(g_sLastReadSub.GetLength()!=0)
	{
		theApp.WriteProfileString(_T("Settings"), _T("LastRead"), 	g_sLastReadSub);
	}
	
}

BOOL CCONTORDlg::CheckOperator(CString sOpCode, CString sPass)
{
	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("SELECT * FROM Operators WHERE (Operators.OperatorID='"+sOpCode+"') AND (Operators.OperatorPasscode='"+sPass+"');"), CADORecordset::openQuery);
	if(bOk) bOk=!rs.IsEof();
	if(bOk)
	{
		g_iActiveOperator=(int(sOpCode[0])-int('0'))*100+(int(sOpCode[1])-int('0'))*10+(int(sOpCode[0])-int('0'));
	}
	rs.Close();
	return bOk;	
}

LRESULT CCONTORDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message==m_uPrepareMsg)
	{
		if(m_bIsOnFirstPage)
		{
			if(theApp.GetProfileInt(_T("Settings"), _T("HasNotTransferedData"), 0)==1)
			{
				CHasNotTransferedDataDlg ndlg;
				ndlg.DoModal();
			}
			else
			{
				OpenDatabase();
				CReadDataProgressDlg dlg;
				dlg.DoModal();
				g_sLastReadSub=_T("");
				theApp.WriteProfileString(_T("Settings"), _T("LastRead"), 	g_sLastReadSub);		
			}
		}
		else
		{
			CAlertBoxDlg adlg;
			adlg.m_sMyAlert=_T("»—«Ì «Ì‰ ò«— »«Ìœ »Â ’›ÕÂ «’·Ì »—ê—œÌœ.");
			adlg.DoModal();
		}
	}
	if(message==m_uGenFilesMsg)
	{
		if(m_bIsOnFirstPage)
		{
			OpenDatabase();
			CWriteDataProgressDlg dlg;
			dlg.DoModal();
		}
		else
		{
			CAlertBoxDlg adlg;
			adlg.m_sMyAlert=_T("»—«Ì «Ì‰ ò«— »«Ìœ »Â ’›ÕÂ «’·Ì »—ê—œÌœ.");
			adlg.DoModal();
		}
	}
	if(message==m_uDataTransfered)
	{
		theApp.WriteProfileInt(_T("Settings"), _T("HasNotTransferedData"), 0);
	}
	return CDialog::WindowProc(message, wParam, lParam);
}



void CCONTORDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	
		CRect rect;
		GetClientRect(&rect);
		BITMAP bmp;

		::GetObject(m_hBmpBkgnd, sizeof(bmp), &bmp);
		HDC hDC = ::CreateCompatibleDC(NULL);
		if(hDC != NULL)
		{
			::SelectObject(hDC, m_hBmpBkgnd);
			::BitBlt(dc.m_hDC, 0, 0, rect.Width(), rect.Height(), hDC, 0, 0, SRCCOPY);
			::DeleteDC(hDC);
		}


		dc.SetBkMode(TRANSPARENT);

		CFont *def_font = dc.SelectObject(&m_Font);

		CRect trect;

		trect.left=0;
		trect.right=324;
		trect.top=140;
		trect.bottom=180;
		CString sCaption=_T("›‰ ¬Ê—«‰ œ«œÂ «›“«— ò«—«");		
		dc.SetTextColor(RGB(255, 255, 255));
		dc.DrawText(Arabize(sCaption), trect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		dc.SetTextColor(RGB(0, 0, 0));
		trect.top=160;
		trect.bottom=200;
		sCaption=_T("------");
		dc.DrawText(sCaption, trect, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		trect.left=162;
		trect.right=324;
		trect.top=180;
		trect.bottom=220;
		sCaption=_T(" «—ÌŒ «„—Ê“ : ");		
		dc.DrawText(Arabize(sCaption), trect, DT_SINGLELINE|DT_VCENTER|DT_LEFT);
		trect.left=0;
		trect.right=162;
		dc.SetTextColor(RGB(255, 255, 255));
		dc.DrawText(ComputeTodayDate(), trect, DT_SINGLELINE|DT_VCENTER|DT_RIGHT);		
		dc.SetTextColor(RGB(0, 0, 0));
		sCaption=_T("‘«—é »« —Ì : ");		
		trect.left=162;
		trect.right=324;
		trect.top=200;
		trect.bottom=240;
		dc.DrawText(Arabize(sCaption), trect, DT_SINGLELINE|DT_VCENTER|DT_LEFT);
		trect.left=0;
		trect.right=162;
		dc.SetTextColor(RGB(255, 255, 255));
		dc.DrawText(GetBatteryLifePercent(), trect, DT_SINGLELINE|DT_VCENTER|DT_RIGHT);		
		dc.SetTextColor(RGB(0, 0, 0));
		sCaption=_T("ÊÌ—«Ì‘ »—‰«„Â : ");		
		trect.left=162;
		trect.right=324;
		trect.top=220;
		trect.bottom=260;
		dc.DrawText(Arabize(sCaption), trect, DT_SINGLELINE|DT_VCENTER|DT_LEFT);
		trect.left=0;
		trect.right=162;
		dc.SetTextColor(RGB(255, 255, 255));
		dc.DrawText(_T("1.0.0"), trect, DT_SINGLELINE|DT_VCENTER|DT_RIGHT);		
		dc.SetTextColor(RGB(0, 0, 0));
		dc.SelectObject(def_font);
}


CString CCONTORDlg::ComputeTodayDate()
{
	CString sNowDate;
	SYSTEMTIME systime;
	int		m_JD;
	int		m_JM;
	int		m_JY;
	int		m_GD;
	int		m_GM;
	int		m_GY;

	GetLocalTime(&systime);
	m_GD = systime.wDay-1;
	m_GM = systime.wMonth-1;
	m_GY = systime.wYear;
	gregorian_to_jalali(&m_JY, &m_JM, &m_JD, m_GY, m_GM+1, m_GD+1);


	CString sTemp;
	sTemp.Format(_T("%4.d"), m_JY);
	sNowDate=CString(sTemp[2])+sTemp[3];
	sNowDate=sNowDate+_T("/");
	sTemp.Format(_T("%.2d"), m_JM);
	sNowDate=sNowDate+sTemp;
	sNowDate=sNowDate+_T("/");
	sTemp.Format(_T("%.2d"), m_JD);
	sNowDate=sNowDate+sTemp;	
	return sNowDate;
}

CString CCONTORDlg::GetBatteryLifePercent()
{
	SYSTEM_POWER_STATUS_EX	PowerStatus;
	BOOL bRet;
	CString sPercent=_T("?");
	bRet = GetSystemPowerStatusEx(&PowerStatus, TRUE);
	if (bRet == FALSE)
	{
		return sPercent;
	}
	if (PowerStatus.BatteryLifePercent <= 100)
	{
		sPercent.Format(_T("%d"), PowerStatus.BatteryLifePercent);
		sPercent=_T("%")+sPercent;
	}
	return sPercent;
}

void CCONTORDlg::OnShowinformaton() 
{
	m_bIsOnFirstPage=FALSE;
	CSettingsDlg	dlg;
	dlg.m_bEnteredMeterReading=m_bEnteredMeterReading;
	dlg.DoModal();
	m_bIsOnFirstPage=TRUE;
}

BOOL CCONTORDlg::VerifySoftwareKey()
{

	ELECTRONIC_SERIAL_NUMBER s_ESN;
	memset(&s_ESN,0,sizeof(ELECTRONIC_SERIAL_NUMBER));
	SI_INIT(&s_ESN);
	DWORD dwResult = GetESN(&s_ESN);
	if(0 == dwResult)
		{
			MessageBox(_T("error!"));
			return FALSE;
		}

	CString m_sHardwareKey=s_ESN.wszESN;


	CString str=m_sHardwareKey;
	
	int iLen=str.GetLength();


	CString sTemp;
	m_sHardwareKey=_T("");
	for(int i=1; i<iLen; i++)
	{
		sTemp.Format(_T("%02u"), (BYTE)str[i]);
		m_sHardwareKey=m_sHardwareKey+sTemp;
	}

	str=_T("");
	int jReplacements=0;
	for(i=0; i<m_sHardwareKey.GetLength(); i+=2)
	{
		str=str+m_sHardwareKey[m_sHardwareKey.GetLength()-i-2];
		if(m_sHardwareKey[m_sHardwareKey.GetLength()-i-2]=='4')
		{
			if( (m_sHardwareKey[i+1]=='8') || (m_sHardwareKey[i+1]=='9') )
			{
				str=str+m_sHardwareKey[i+1];
			}
			else
			{
				jReplacements++;
				WCHAR wCodes[2];
				wCodes[1]=0;
				wCodes[0]=0x0038+jReplacements%2;
				CString sCodes=wCodes;
				str=str+wCodes;
			}
		}
		else
		{
			if( m_sHardwareKey[i+1]<'8' )
			{
				str=str+m_sHardwareKey[i+1];
			}
			else
			{
				jReplacements++;
				WCHAR wCodes[2];
				wCodes[1]=0;
				wCodes[0]=0x0030+jReplacements%8;
				CString sCodes=wCodes;
				str=str+wCodes;
			}
		}		
	}

	char ctr[256];
	for(i=0; i<str.GetLength(); i+=2)
	{
		ctr[i/2]=(int(str[i])-0x0030)*10+(int(str[i+1])-0x0030);
	}
	ctr[str.GetLength()/2]=0;
	WCHAR wtr[256];
	MakeCharArrayWCHARARRAY(ctr, wtr);
	str=wtr;

	CString sRegisteryActivationCode=theApp.GetProfileString(_T("Settings"), _T("Serial Number"),_T(""));
	
	return (sRegisteryActivationCode==str);

}


void CCONTORDlg::OpenDatabase()
{
	m_bEnteredMeterReading=TRUE;
	if(!g_db.IsOpen())
	{
	CString sDefaultStorage=_T("\\contor.cdb");
	if(theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==1)
	{
		sDefaultStorage=_T("\\Storage Card\\contor.cdb");
	}
	CString sConnection=_T("Data Source=");
	sConnection=sConnection+sDefaultStorage;

	if(!g_db.Open(sConnection))
	{
		//AfxMessageBox(_T("Cannot open database. \nTrying to copy default db."));
		if(!CopyFile(_T("\\Application\\contor\\contor.cdb"), sDefaultStorage, FALSE))
		{
			if(theApp.GetProfileInt(_T("Settings"), _T("Storage"), 0)==1)
			{
				AfxMessageBox(_T("Error Copying Database. \nTrying to change storgae"));
				theApp.WriteProfileInt(_T("Settings"), _T("Storage"), 0);
				sDefaultStorage=_T("\\contor.cdb");
				sConnection=_T("Data Source=");
				sConnection=sConnection+sDefaultStorage;
			}
			else
			{
				AfxMessageBox(_T("Error Copying Database."));
				return;
			}
		}
		//TRY TO CHANGE DEFAULT STORAGE:
		if(!g_db.Open(sConnection))
		{
			AfxMessageBox(_T("Cannot open database."));
			return;
		}
	}	
	}
}
