// SCommView.h : interface of the CSCommView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCOMMVIEW_H__2BEC220C_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
#define AFX_SCOMMVIEW_H__2BEC220C_96DD_11D2_B015_40DA42C100D5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSCommView : public CScrollView
{
protected: // create from serialization only
	CSCommView();
	DECLARE_DYNCREATE(CSCommView)

// Attributes
public:
	CSCommDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCommView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSCommView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSCommView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SCommView.cpp
inline CSCommDoc* CSCommView::GetDocument()
   { return (CSCommDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOMMVIEW_H__2BEC220C_96DD_11D2_B015_40DA42C100D5__INCLUDED_)
