// PDTMngrKeygenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PDTMngrKeygen.h"
#include "PDTMngrKeygenDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDTMngrKeygenDlg dialog

CPDTMngrKeygenDlg::CPDTMngrKeygenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPDTMngrKeygenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPDTMngrKeygenDlg)
	m_sPassword = _T("");
	m_sHardwareKey = _T("");
	m_sActivationCode = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPDTMngrKeygenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPDTMngrKeygenDlg)
	DDX_Control(pDX, IDC_CON2, m_c3);
	DDX_Control(pDX, IDC_EHARDWAREKEY, m_c2);
	DDX_Control(pDX, IDC_EACTIVATIONCODE, m_c1);
	DDX_Text(pDX, IDC_EPASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_EHARDWAREKEY, m_sHardwareKey);
	DDX_Text(pDX, IDC_EACTIVATIONCODE, m_sActivationCode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPDTMngrKeygenDlg, CDialog)
	//{{AFX_MSG_MAP(CPDTMngrKeygenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CON, OnCon)
	ON_BN_CLICKED(IDC_CON2, OnCon2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPDTMngrKeygenDlg message handlers

BOOL CPDTMngrKeygenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_c1.ShowWindow(SW_HIDE);
	m_c2.ShowWindow(SW_HIDE);
	m_c3.ShowWindow(SW_HIDE);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPDTMngrKeygenDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CPDTMngrKeygenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPDTMngrKeygenDlg::OnCon() 
{
	UpdateData();
	if (m_sPassword=="hghdhhdihd") 
	{
		m_c1.ShowWindow(SW_SHOW);
		m_c2.ShowWindow(SW_SHOW);
		m_c3.ShowWindow(SW_SHOW);
	}
}

void CPDTMngrKeygenDlg::OnCon2() 
{

	UpdateData();


	
	CString str="S";
	str+=m_sHardwareKey;
	
	int iLen=str.GetLength();


	CString sTemp;
	CString sHardwareKey;
	sHardwareKey=_T("");
	for(int i=1; i<iLen; i++)
	{
		sTemp.Format(_T("%02u"), (BYTE)str[i]);
		sHardwareKey=sHardwareKey+sTemp;
	}

	str=_T("");
	int jReplacements=0;
	for(i=0; i<sHardwareKey.GetLength(); i+=2)
	{
		str=str+sHardwareKey[sHardwareKey.GetLength()-i-2];
		if(sHardwareKey[sHardwareKey.GetLength()-i-2]=='4')
		{
			if( (sHardwareKey[i+1]=='8') || (sHardwareKey[i+1]=='9') )
			{
				str=str+sHardwareKey[i+1];
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
			if( sHardwareKey[i+1]<'8' )
			{
				str=str+sHardwareKey[i+1];
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
	str=ctr;

	m_sActivationCode=str;



	UpdateData(FALSE);
	

}
