// PathSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "PathSelectDlg.h"
#include "ado.h"
#include "NotFoundPathDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathSelectDlg dialog
extern CADODatabase	g_db;
extern CString g_sLastReadSub;

CPathSelectDlg::CPathSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPathSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPathSelectDlg)
	m_iNowPath = -1;
	//}}AFX_DATA_INIT
}


void CPathSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPathSelectDlg)
	DDX_Control(pDX, IDC_CPATHCOMBO, m_ctlPathCombo);
	DDX_CBIndex(pDX, IDC_CPATHCOMBO, m_iNowPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPathSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CPathSelectDlg)
	ON_BN_CLICKED(IDC_PATHBEGIN, OnPathbegin)
	ON_BN_CLICKED(IDC_PATHEND, OnPathend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathSelectDlg message handlers

BOOL CPathSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();

	FillCombo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPathSelectDlg::FullScreenMe()
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

void CPathSelectDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SPATHSELECTTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SPATHSELECTTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_PATHBEGIN)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_PATHBEGIN)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_PATHEND)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_PATHEND)->SetWindowText(Arabize(sWindowText));

}

void CPathSelectDlg::FillCombo()
{
	int iIndex=0;
	CADORecordset rs=CADORecordset(&g_db);
	rs.Open(_T("SELECT PathNumber FROM PathNumbers ORDER BY PathNumber;"), CADORecordset::openQuery);
	while(!rs.IsEof())
	{
		CString sPathNumber;
		rs.GetFieldValue(_T("PathNumber"), sPathNumber);
		m_ctlPathCombo.AddString(sPathNumber);
		if(m_sLastAD.Left(5)==sPathNumber)
		{
			m_iNowPath=iIndex;
		}
		rs.MoveNext();
		iIndex++;
	}
	rs.Close();	
	UpdateData(FALSE);
}

void CPathSelectDlg::OnPathbegin() 
{
	UpdateData();
	CString sNowPath;
	m_ctlPathCombo.GetLBText(m_iNowPath, sNowPath);
	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("SELECT SubscriptionCode FROM WhiteList WHERE (WhiteList.AddressCode LIKE '"+sNowPath+"%') ORDER BY AddressCode;"), CADORecordset::openQuery);
	if(!bOk)
		OnOK();	
	if(rs.IsEof())
	{
		CNotFoundPathDlg dlg;
		dlg.DoModal();
	}
	else
	{
		rs.GetFieldValue(_T("SubscriptionCode"), g_sLastReadSub);
	}
	rs.Close();
}

void CPathSelectDlg::OnPathend() 
{
	UpdateData();
	CString sNowPath;
	m_ctlPathCombo.GetLBText(m_iNowPath, sNowPath);
	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("SELECT SubscriptionCode FROM WhiteList WHERE (WhiteList.AddressCode LIKE '"+sNowPath+"%') ORDER BY AddressCode DESC;"), CADORecordset::openQuery);
	if(!bOk)
		OnOK();	
	if(rs.IsEof())
	{
		CNotFoundPathDlg dlg;
		dlg.DoModal();
	}
	else
	{
		rs.GetFieldValue(_T("SubscriptionCode"), g_sLastReadSub);
	}
	rs.Close();	
}
