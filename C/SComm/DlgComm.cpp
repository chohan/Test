// DlgComm.cpp : implementation file
//

#include "stdafx.h"
#include "SComm.h"
#include "DlgComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgComm dialog


CDlgComm::CDlgComm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgComm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgComm)
	//}}AFX_DATA_INIT
}


void CDlgComm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgComm)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgComm, CDialog)
	//{{AFX_MSG_MAP(CDlgComm)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgComm message handlers
