// SCommDoc.h : interface of the CSCommDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCOMMDOC_H__2BEC220A_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
#define AFX_SCOMMDOC_H__2BEC220A_96DD_11D2_B015_40DA42C100D5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSCommDoc : public CDocument
{
protected: // create from serialization only
	CSCommDoc();
	DECLARE_DYNCREATE(CSCommDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCommDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSCommDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSCommDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOMMDOC_H__2BEC220A_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
