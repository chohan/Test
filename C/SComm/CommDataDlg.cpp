// CommDataDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "ads.h"
#include "CommDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommDataDlg dialog

CCommDataDlg::CCommDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommDataDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCommDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommDataDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommDataDlg, CDialog)
	//{{AFX_MSG_MAP(CCommDataDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommDataDlg message handlers

BOOL CCommDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Create the Edit control that sits in the mainframe window.
	if (!m_edit.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_WANTRETURN|
		ES_MULTILINE|ES_AUTOVSCROLL,CRect(0,0,450,200),this,ID_TERMEDIT))
	{
		TRACE0("Failed to create edit control\n");
		return -1;      // fail to create
	}
	m_edit.SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
