
// gld3d_Base_SDI1View.h : interface of the Cgld3d_Base_SDI1View class
//

#pragma once
#include "../../BaseClass/GLView.h"

class Cgld3d_Base_SDI1View : public CGLView
//class Cgld3d_Base_SDI1View : public CView
{
protected: // create from serialization only
	Cgld3d_Base_SDI1View();
	DECLARE_DYNCREATE(Cgld3d_Base_SDI1View)

// Attributes
public:
	Cgld3d_Base_SDI1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cgld3d_Base_SDI1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in gld3d_Base_SDI1View.cpp
inline Cgld3d_Base_SDI1Doc* Cgld3d_Base_SDI1View::GetDocument() const
   { return reinterpret_cast<Cgld3d_Base_SDI1Doc*>(m_pDocument); }
#endif

