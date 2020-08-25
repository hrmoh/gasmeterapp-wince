// WriteDataProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "WriteDataProgressDlg.h"
#include "ado.h"
#include "FilesReadyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWriteDataProgressDlg dialog

extern CADODatabase	g_db;


CWriteDataProgressDlg::CWriteDataProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteDataProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWriteDataProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWriteDataProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWriteDataProgressDlg)
	DDX_Control(pDX, IDC_WRITEPROGRESS, m_ctlWriteProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWriteDataProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CWriteDataProgressDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriteDataProgressDlg message handlers

BOOL CWriteDataProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CenterWindow();
	m_ctlWriteProgress.SetRange(0, 100);

	SetTimer(IDC_WRITEDATATIMER, 100, NULL);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWriteDataProgressDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==IDC_WRITEDATATIMER)
	{
		KillTimer(IDC_WRITEDATATIMER);
		WriteOUTPUTDAT();
		WriteERRORSDAT();
		CFilesReadyDlg dlg;
		dlg.DoModal();
		OnOK();
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CWriteDataProgressDlg::WriteOUTPUTDAT()
{
	CFile fOutputDAT(_T("\\OUTPUT.DAT"), CFile::modeCreate|CFile::modeWrite);
	CADORecordset rs=CADORecordset(&g_db);
	rs.Open(_T("DeviceOutput"), CADORecordset::openTable);
	int iCustomersWritten=0;
	int iCustomersNum=rs.GetRecordCount();
	while(!rs.IsEof())
	{
		CString sSubscriptionCode;
		rs.GetFieldValue(_T("SubscriptionCode"), sSubscriptionCode);
		char cSubscriptionCode[15];
		for(int i=0; i<15; i++) cSubscriptionCode[i]=((char)sSubscriptionCode[i]);
		fOutputDAT.Write(cSubscriptionCode, 15);
		double fNow;
		rs.GetFieldValue(_T("CurrentCounter"),		fNow	);	
		CString sCurrentCounter;
		sCurrentCounter.Format(_T("%010.0f"), fNow);	
		char cCurrentCounter[10];
		for(i=0; i<10; i++) cCurrentCounter[i]=((char)sCurrentCounter[i]);
		fOutputDAT.Write(cCurrentCounter, 10);
		CString sRDate;
		rs.GetFieldValue(_T("RDate"), sRDate);
		char cRDate[6];
		for(i=0; i<6; i++) cRDate[i]=((char)sRDate[i]);
		fOutputDAT.Write(cRDate, 6);
		CString sRTime;
		rs.GetFieldValue(_T("RTime"), sRTime);
		char cRTime[6];
		for(i=0; i<6; i++) cRTime[i]=((char)sRTime[i]);
		fOutputDAT.Write(cRTime, 6);
		int iWho;
		rs.GetFieldValue(_T("WhoReports"), iWho);
		BYTE bWho=(BYTE)iWho;
		fOutputDAT.Write(&bWho, 1);
		m_ctlWriteProgress.SetPos(int(float(++iCustomersWritten)/float(iCustomersNum)*100));
		rs.MoveNext();
	}
	rs.Close();
	fOutputDAT.Close();
}

void CWriteDataProgressDlg::WriteERRORSDAT()
{
	CFile fErrorsDAT(_T("\\ERRORS.DAT"), CFile::modeCreate|CFile::modeWrite);
	CADORecordset rs=CADORecordset(&g_db);
	rs.Open(_T("OutputErrors"), CADORecordset::openTable);
	int iCustomersWritten=0;
	int iCustomersNum=rs.GetRecordCount();
	while(!rs.IsEof())
	{
		CString sSubscriptionCode;
		rs.GetFieldValue(_T("SubscriptionCode"), sSubscriptionCode);
		char cSubscriptionCode[15];
		for(int i=0; i<15; i++) cSubscriptionCode[i]=((char)sSubscriptionCode[i]);
		fErrorsDAT.Write(cSubscriptionCode, 15);
		int iError;
		rs.GetFieldValue(_T("ErrorCode"),		iError	);	
		if( ((BYTE)iError)>13)
			iError+=4;
		BYTE bError=(BYTE)iError;
		fErrorsDAT.Write(&bError, 1);
		CString sRDate;
		rs.GetFieldValue(_T("ErrorDate"), sRDate);
		char cRDate[6];
		for(i=0; i<6; i++) cRDate[i]=((char)sRDate[i]);
		fErrorsDAT.Write(cRDate, 6);
		CString sRTime;
		rs.GetFieldValue(_T("ErrorTime"), sRTime);
		char cRTime[6];
		for(i=0; i<6; i++) cRTime[i]=((char)sRTime[i]);
		fErrorsDAT.Write(cRTime, 6);
		int iWho;
		rs.GetFieldValue(_T("WhoReports"), iWho);
		BYTE bWho=(BYTE)iWho;
		fErrorsDAT.Write(&bWho, 1);
		m_ctlWriteProgress.SetPos(int(float(++iCustomersWritten)/float(iCustomersNum)*100));
		rs.MoveNext();
	}
	rs.Close();
	fErrorsDAT.Close();
}
