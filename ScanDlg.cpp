// ScanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "ScanDlg.h"
#include "ado.h"
#include "SearchSerialDlg.h"
#include "CustomersInfoDlg.h"
#include "NotFoundDlg.h"
#include "SearchMethodSelDlg.h"
#include "StatsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CScanDlg dialog
extern CADODatabase	g_db;

CScanDlg::CScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bRequestPending=FALSE;
	m_bTriggerFlag=FALSE;
	m_hScanner= NULL;
	m_lpScanBuffer=NULL;
	m_bStopScanning=FALSE;
}


void CScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanDlg, CDialog)
	//{{AFX_MSG_MAP(CScanDlg)
	ON_MESSAGE(UM_SCAN, OnScanDone)    
	ON_MESSAGE(UM_STOPSCANNING, OnStopScan)
	ON_BN_CLICKED(IDC_CHANGEMETHEOD, OnChangemetheod)
	ON_BN_CLICKED(IDC_SOFTSCAN, OnSoftscan)
	ON_BN_CLICKED(IDC_SETTINGS, OnSettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanDlg message handlers

BOOL CScanDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_iDoNext=-1;
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	PrepareScanning();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScanDlg::PrepareScanning()
{
	DWORD			dwResult;

	// Open scanner, prepare for scanning, 
	// and submit the first read request
	TCHAR			szScannerName[MAX_PATH] = TEXT("SCN1:");	// default scanner name
	DWORD			dwScanSize				= 7095;				// default scan buffer size	
	DWORD			dwScanTimeout			= 0;				// default timeout value (0 means no timeout)	
	BOOL			bUseText				= TRUE;
	BOOL			bStopScanning			= FALSE;

	m_bTriggerFlag=FALSE;
	dwResult = SCAN_Open(szScannerName, &m_hScanner);
	if ( dwResult != E_SCN_SUCCESS )
	{	
		//ErrorExit(hwnd, IDS_FAILURE, TEXT("SCAN_Open"));
	}

	dwResult = SCAN_Enable(m_hScanner);
	if ( dwResult != E_SCN_SUCCESS )
	{

	}

	m_lpScanBuffer = SCAN_AllocateBuffer(bUseText, dwScanSize);
	if (m_lpScanBuffer == NULL)
	{
	}

	dwResult = SCAN_ReadLabelMsg(m_hScanner,
								 m_lpScanBuffer,
								 m_hWnd,
								 UM_SCAN,
								 dwScanTimeout,
								 NULL);
	if ( dwResult != E_SCN_SUCCESS )
		;
//		ErrorExit(hwnd, IDS_FAILURE, TEXT("SCAN_ReadLabelMsg"));
	else
		m_bRequestPending = TRUE;
}

void CScanDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_CHANGEMETHEOD)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_CHANGEMETHEOD)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SETTINGS)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SETTINGS)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SADRTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SADRTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SADRTITLE2)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SADRTITLE2)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SOFTSCAN)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SOFTSCAN)->SetWindowText(Arabize(sWindowText));
	
}

void CScanDlg::FullScreenMe()
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


void CScanDlg::OnScanDone()
{
//			TCHAR			szLabelType[10];
//			TCHAR			szLen[MAX_PATH];
			m_bRequestPending = FALSE;

			// Clear the soft trigger
			m_bTriggerFlag = FALSE;

			CString sWindowText=_T("ÝÚÇáÓÇÒí ÇÓ˜äÑ Èå ÕæÑÊ äÑã ÇÝÒÇÑí");
			GetDlgItem(IDC_SOFTSCAN)->SetWindowText(Arabize(sWindowText));

			CString m_sSearch=_T("121");

			// Get scan result from the scan buffer, and display it
			if ( m_lpScanBuffer == NULL )
				MessageBox(_T("Error"));

			switch (SCNBUF_GETSTAT(m_lpScanBuffer))
			{ 
				case E_SCN_DEVICEFAILURE:
					MessageBox(_T("Error"));
					break;

				case E_SCN_READPENDING:

					MessageBox(_T("Pending"));
					break;

				case E_SCN_READCANCELLED:

					if (m_bStopScanning)
					{	// complete the second step of UM_STOPSCANNING
						SendMessage(UM_STOPSCANNING,0,0L);	
						return;
					}
					if (!GetFocus())	
						break;	// Do nothing if read was cancelled while deactivation
					MessageBox(_T("Canceled"));
					break;
			
				case E_SCN_SUCCESS:
				
					m_sSearch=m_sSearch+CString((LPTSTR)SCNBUF_GETDATA(m_lpScanBuffer));

					CADORecordset rs=CADORecordset(&g_db);
					BOOL bOk=rs.Open(_T("SELECT * FROM WhiteList WHERE (WhiteList.SubscriptionCode LIKE '%"+m_sSearch+"%');"), CADORecordset::openQuery);
					if(bOk)
					{
						if(rs.IsEof())
						{
							CNotFoundDlg dlg;
							dlg.DoModal();
							PrepareScanning();
						}
						else
						{
							CCustomersInfoDlg dlg;
							rs.GetFieldValue(_T("PrevCounter"),		dlg.m_fPrev	);
							CString sPrevDate;
							rs.GetFieldValue(_T("PrevDate"),		sPrevDate	);
							dlg.m_sPrevDate=CString(sPrevDate[0])+sPrevDate[1]+"/"+sPrevDate[2]+sPrevDate[3]+"/"+sPrevDate[4]+sPrevDate[5];	
							rs.GetFieldValue(_T("Address"),		dlg.m_sAddress	);
							rs.GetFieldValue(_T("SubscriptionCode"),		dlg.m_sSubscriptionCode	);
							rs.GetFieldValue(_T("AddressCode"),		dlg.m_sAD	);	
							CString sNam;
							rs.GetFieldValue(_T("FName"),		sNam	);
							rs.GetFieldValue(_T("FLName"),		dlg.m_sNam	);	
							dlg.m_sNam=sNam+" "+dlg.m_sNam;
							rs.GetFieldValue(_T("CounterSerial"),		dlg.m_sSer	);	
							dlg.DoModal();
							PrepareScanning();
						}
					rs.Close();	
					}

					
					// Format label type as a hex constant for display
					/*
					wsprintf(szLabelType, TEXT("0x%.2X"), SCNBUF_GETLBLTYP(m_lpScanBuffer));
					MessageBox(szLabelType);

					wsprintf(szLen, TEXT("%d"), SCNBUF_GETLEN(m_lpScanBuffer));
					MessageBox(szLen);
					*/

					break;
			}

}

void CScanDlg::OnStopScan()
{
			// We stop scanning in two steps: first, cancel any pending read 
			// request; second, after there is no more pending request, disable 
			// and close the scanner. We may need to do the second step after 
			// a UM_SCAN message told us that the cancellation was completed.
			if (!m_bStopScanning && m_bRequestPending)													
				SCAN_Flush(m_hScanner);

			if (!m_bRequestPending)			
			{							 
				SCAN_Disable(m_hScanner);

				if (m_lpScanBuffer)
					SCAN_DeallocateBuffer(m_lpScanBuffer);

				SCAN_Close(m_hScanner);

			}
			m_bStopScanning = TRUE;
}

void CScanDlg::OnOK() 
{
	OnStopScan();
	CDialog::OnOK();
}

void CScanDlg::OnChangemetheod() 
{
	CSearchMethodSelDlg	dlg;
	dlg.m_iSelectedMethod=0;
	dlg.DoModal();
	if(dlg.m_iSelectedMethod!=0)
	{
		m_iDoNext=dlg.m_iSelectedMethod;
		OnOK();
	}	
}

void CScanDlg::OnSoftscan() 
{
	CString sWindowText=_T("ÇÓ˜äÑ äÑã ÇÝÒÇÑí ÛíÑÝÚÇá ÔæÏ");
	if(m_bTriggerFlag)
		sWindowText=_T("ÝÚÇáÓÇÒí ÇÓ˜äÑ Èå ÕæÑÊ äÑã ÇÝÒÇÑí");
	GetDlgItem(IDC_SOFTSCAN)->SetWindowText(Arabize(sWindowText));

	m_bTriggerFlag = !m_bTriggerFlag;
	SCAN_SetSoftTrigger(m_hScanner,&m_bTriggerFlag);
}

void CScanDlg::OnSettings() 
{
	CStatsDlg	dlg;
	dlg.DoModal();	
}
