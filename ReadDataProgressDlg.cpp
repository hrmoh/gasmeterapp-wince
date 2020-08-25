// ReadDataProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CONTOR.h"
#include "ReadDataProgressDlg.h"
#include "ado.h"
#include "PersianSupport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CCONTORApp theApp;
extern CADODatabase	g_db;
extern BOOL g_bEnterUsingAd;
extern BOOL g_bEnterUsingSub;
extern BOOL g_bCheckPass;
extern CString g_sSettingsPath;

/////////////////////////////////////////////////////////////////////////////
// CReadDataProgressDlg dialog


CReadDataProgressDlg::CReadDataProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadDataProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadDataProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReadDataProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadDataProgressDlg)
	DDX_Control(pDX, IDC_READPROGRESS, m_ctlReadProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadDataProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CReadDataProgressDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadDataProgressDlg message handlers

BOOL CReadDataProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	CenterWindow();
	m_ctlReadProgress.SetRange(0, 100);

	SetTimer(IDC_READDATATIMER, 100, NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReadDataProgressDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==IDC_READDATATIMER)
	{
		KillTimer(IDC_READDATATIMER);
		ReadCONTORDAT();
		ReadCONFIGDAT();
		DeleteFile(_T("\\CONTOR.DAT"));
		DeleteFile(_T("\\CONFIG.DAT"));
		OnOK();
	}
	CDialog::OnTimer(nIDEvent);
}

void CReadDataProgressDlg::ReadCONTORDAT()
{	
	CFile fContorDAT(_T("\\CONTOR.DAT"), CFile::modeRead);
	
	int iCustomersNum=fContorDAT.GetLength()/144;
	
	char pStringField[46];
	WCHAR wStringField[46];

	int iCustomersRead=0;


	g_db.Execute(_T("DELETE FROM WhiteList"));
	g_db.Execute(_T("DELETE FROM DeviceOutput"));
	g_db.Execute(_T("DELETE FROM OutputErrors"));
	
	CADORecordset rs=CADORecordset(&g_db);
	rs.Open(_T("WhiteList"), CADORecordset::openTable);

	while(fContorDAT.Read(pStringField, 15)==15)//subscription
	{
		m_ctlReadProgress.SetPos(int(float(++iCustomersRead)/float(iCustomersNum)*100));
		rs.AddNew();

		pStringField[15]='\0';
		CString m_sStringField=pStringField;
		rs.SetFieldValue(_T("SubscriptionCode"),		m_sStringField	);

		fContorDAT.Read(pStringField, 18); //name
		pStringField[18]='\0';
		MakeCharArrayWCHARARRAY(pStringField, wStringField);
		m_sStringField=wStringField;
		rs.SetFieldValue(_T("FName"),m_sStringField);

		fContorDAT.Read(pStringField, 22); //family
		pStringField[22]='\0';
		MakeCharArrayWCHARARRAY(pStringField, wStringField);
		m_sStringField=wStringField;
		rs.SetFieldValue(_T("FLName"),		m_sStringField	);

		fContorDAT.Read(pStringField, 10); //address code
		pStringField[10]='\0';
		m_sStringField=pStringField;
		rs.SetFieldValue(_T("AddressCode"),		m_sStringField	);

		fContorDAT.Read(pStringField, 10); //Counter Serial
		pStringField[10]='\0';
		m_sStringField=pStringField;
		rs.SetFieldValue(_T("CounterSerial"),		m_sStringField	);

		int iFieldValue;

		fContorDAT.Read(&iFieldValue, sizeof(int)); //consumption
		rs.SetFieldValue(_T("ConsumptionKind"),		iFieldValue	);

		fContorDAT.Read(&iFieldValue, sizeof(int)); //capacity
		rs.SetFieldValue(_T("Capacity"),		iFieldValue	);

		fContorDAT.Read(pStringField, 6); //PrevDate
		pStringField[6]='\0';
		m_sStringField=pStringField;
		rs.SetFieldValue(_T("PrevDate"),		m_sStringField	);

		fContorDAT.Read(pStringField, 10); //PrevCounter
		pStringField[10]='\0';
		m_sStringField=pStringField;
		rs.SetFieldValue(_T("PrevCounter"),		m_sStringField	);

		fContorDAT.Read(pStringField, 45); //address
		pStringField[45]='\0';
		MakeCharArrayWCHARARRAY(pStringField, wStringField);
		m_sStringField=wStringField;
		rs.SetFieldValue(_T("Address"),		m_sStringField	);


		rs.SetFieldValue(_T("AOrder"),		iCustomersRead	);


		rs.Update();

	}

	rs.Close();
	

}

void CReadDataProgressDlg::ReadCONFIGDAT()
{
//	CREATE TABLE [Operators] ([OperatorID] SMALLINT, [OperatorName] TEXT, [OperatorPassCode] TEXT
	CFile fConfigDAT(_T("\\CONFIG.DAT"), CFile::modeRead);
	//Enter using ad:
	char c;
	fConfigDAT.Read(&c, 1);
	g_bEnterUsingAd=(c=='1');
	fConfigDAT.Read(&c, 1);
	g_bEnterUsingSub=(c=='1');
	fConfigDAT.Read(&c, 1);
	g_bCheckPass=(c=='1');


	if(g_bEnterUsingAd)
	{
		theApp.WriteProfileInt(_T("Settings"), _T("EnterUsingAd"), 1);
		theApp.WriteProfileInt(_T("Settings"), _T("LastSearchMethod"), 4);
	}
	else
	{
		theApp.WriteProfileInt(_T("Settings"), _T("EnterUsingAd"), 0);
		theApp.WriteProfileInt(_T("Settings"), _T("LastSearchMethod"), 0);
	}
	if(g_bEnterUsingSub)
		theApp.WriteProfileInt(_T("Settings"), _T("EnterUsingSub"), 1);
	else
		theApp.WriteProfileInt(_T("Settings"), _T("EnterUsingSub"), 0);
	if(g_bCheckPass)
		theApp.WriteProfileInt(_T("Settings"), _T("CheckPass"), 1);
	else
		theApp.WriteProfileInt(_T("Settings"), _T("CheckPass"), 0);

	char pStringField[51];
	WCHAR wStringField[51];
	pStringField[50]=0;
	wStringField[50]=0;

	char cNum[51];
	fConfigDAT.Read(cNum, 8);
	cNum[8]=0;
	MakeCharArrayWCHARARRAY(cNum, wStringField);
	wStringField[2]='/';
	wStringField[5]='/';
	CString sFileDate=wStringField;
	theApp.WriteProfileString(_T("Settings"), _T("FileDate"), sFileDate);

	g_db.Execute(_T("DELETE FROM Operators"));
	fConfigDAT.Read(cNum, 3);
	cNum[3]=0;
	int iOperatorsNum=(int(cNum[0])-int('0'))*100+(int(cNum[1])-int('0'))*10+int(cNum[2])-int('0');
	if(iOperatorsNum)
	{
		CADORecordset rs=CADORecordset(&g_db);
		rs.Open(_T("Operators"), CADORecordset::openTable);
		for(int i=0; i<iOperatorsNum; i++)
		{
			rs.AddNew();
			fConfigDAT.Read(cNum, 3);
			cNum[3]=0;
			MakeCharArrayWCHARARRAY(cNum, wStringField);
			CString sNum=wStringField;
			rs.SetFieldValue(_T("OperatorID"),		sNum	);
			fConfigDAT.Read(cNum, 4);
			cNum[4]=0;
			MakeCharArrayWCHARARRAY(cNum, wStringField);
			sNum=wStringField;
			rs.SetFieldValue(_T("OperatorPasscode"),		sNum	);
			fConfigDAT.Read(pStringField, 50); //address
			pStringField[50]='\0';
			int j=0;
			while( (pStringField[j]==' ') && (j<50)) j++;				
			MakeCharArrayWCHARARRAY(&pStringField[j], wStringField);
			CString sStringField=wStringField;
			rs.SetFieldValue(_T("OperatorName"),		sStringField	);
			rs.Update();
		}
		rs.Close();
	}
	fConfigDAT.Read(cNum, 4); //passcode
	cNum[4]=0;
	MakeCharArrayWCHARARRAY(cNum, wStringField);
	theApp.WriteProfileString(_T("Settings"), _T("SettingsPath"), wStringField);

	g_db.Execute(_T("DELETE FROM PathNumbers"));
	CADORecordset rs=CADORecordset(&g_db);
	rs.Open(_T("PathNumbers"), CADORecordset::openTable);

	cNum[5]=0;
	while(fConfigDAT.Read(cNum, 5)==5)
	{
		rs.AddNew();
		MakeCharArrayWCHARARRAY(cNum, wStringField);
		CString sStringField=wStringField;
		rs.SetFieldValue(_T("PathNumber"),		sStringField	);
		rs.Update();
	}
	rs.Close();


	fConfigDAT.Close();

}
