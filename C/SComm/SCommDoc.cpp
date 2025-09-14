// SCommDoc.cpp : implementation of the CSCommDoc class
//

#include "stdafx.h"
#include "SComm.h"

#include "SCommDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSCommDoc

IMPLEMENT_DYNCREATE(CSCommDoc, CDocument)

BEGIN_MESSAGE_MAP(CSCommDoc, CDocument)
	//{{AFX_MSG_MAP(CSCommDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCommDoc construction/destruction

CSCommDoc::CSCommDoc()
{
	// TODO: add one-time construction code here

}

CSCommDoc::~CSCommDoc()
{
}

BOOL CSCommDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSCommDoc serialization

void CSCommDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSCommDoc diagnostics

#ifdef _DEBUG
void CSCommDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSCommDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSCommDoc commands
