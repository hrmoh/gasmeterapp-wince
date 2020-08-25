// SearchSubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "SearchSubDlg.h"
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


extern CADODatabase	g_db;
extern BOOL g_bEnterUsingSub;
/////////////////////////////////////////////////////////////////////////////
// CSearchSubDlg dialog



CSearchSubDlg::CSearchSubDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchSubDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchSubDlg)
	m_sSearch = _T("");
	//}}AFX_DATA_INIT
}


void CSearchSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchSubDlg)
	DDX_Text(pDX, IDC_ESEARCH, m_sSearch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchSubDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchSubDlg)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_CHANGEMETHEOD, OnChangemetheod)
	ON_BN_CLICKED(IDC_SETTINGS, OnSettings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchSubDlg message handlers

BOOL CSearchSubDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_iDoNext=-1;
	
	FullScreenMe();
	CenterWindow();
	PersianizeMe();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSearchSubDlg::PersianizeMe()
{
	CString sWindowText;
	GetDlgItem(IDOK)->GetWindowText(sWindowText);	
	GetDlgItem(IDOK)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SFRAME)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SFRAME)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_ESEARCHTITLE)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_ESEARCHTITLE)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SEARCH)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SEARCH)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_CHANGEMETHEOD)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_CHANGEMETHEOD)->SetWindowText(Arabize(sWindowText));

	GetDlgItem(IDC_SETTINGS)->GetWindowText(sWindowText);	
	GetDlgItem(IDC_SETTINGS)->SetWindowText(Arabize(sWindowText));
}

void CSearchSubDlg::FullScreenMe()
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



void CSearchSubDlg::OnSearch() 
{
	UpdateData();	

	if(m_sSearch.GetLength()<13) return;
	
	CADORecordset rs=CADORecordset(&g_db);
	BOOL bOk=rs.Open(_T("SELECT * FROM WhiteList WHERE (WhiteList.SubscriptionCode LIKE '%"+m_sSearch+"%');"), CADORecordset::openQuery);
	if(bOk)
	{
		if(rs.IsEof())
		{
			CNotFoundDlg dlg;
			dlg.DoModal();
		}
		else
		{
			CCustomersInfoDlg dlg;
			dlg.m_bCanReadValue=g_bEnterUsingSub;
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
		}
	}
	rs.Close();	
}

void CSearchSubDlg::OnChangemetheod() 
{
	CSearchMethodSelDlg	dlg;
	dlg.m_iSelectedMethod=2;
	dlg.DoModal();
	if(dlg.m_iSelectedMethod!=2)
	{
		m_iDoNext=dlg.m_iSelectedMethod;
		OnOK();
	}	
}

void CSearchSubDlg::OnSettings() 
{
	CStatsDlg	dlg;
	dlg.DoModal();	
}
