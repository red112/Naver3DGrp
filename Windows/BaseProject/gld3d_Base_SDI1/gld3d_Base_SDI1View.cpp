
// gld3d_Base_SDI1View.cpp : implementation of the Cgld3d_Base_SDI1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "gld3d_Base_SDI1.h"
#endif

#include "gld3d_Base_SDI1Doc.h"
#include "gld3d_Base_SDI1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cgld3d_Base_SDI1View

IMPLEMENT_DYNCREATE(Cgld3d_Base_SDI1View, CView)

BEGIN_MESSAGE_MAP(Cgld3d_Base_SDI1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cgld3d_Base_SDI1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cgld3d_Base_SDI1View construction/destruction

Cgld3d_Base_SDI1View::Cgld3d_Base_SDI1View()
{
	// TODO: add construction code here

}

Cgld3d_Base_SDI1View::~Cgld3d_Base_SDI1View()
{
}

BOOL Cgld3d_Base_SDI1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cgld3d_Base_SDI1View drawing

void Cgld3d_Base_SDI1View::OnDraw(CDC* /*pDC*/)
{
	Cgld3d_Base_SDI1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// Cgld3d_Base_SDI1View printing


void Cgld3d_Base_SDI1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cgld3d_Base_SDI1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cgld3d_Base_SDI1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cgld3d_Base_SDI1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cgld3d_Base_SDI1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cgld3d_Base_SDI1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cgld3d_Base_SDI1View diagnostics

#ifdef _DEBUG
void Cgld3d_Base_SDI1View::AssertValid() const
{
	CView::AssertValid();
}

void Cgld3d_Base_SDI1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cgld3d_Base_SDI1Doc* Cgld3d_Base_SDI1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cgld3d_Base_SDI1Doc)));
	return (Cgld3d_Base_SDI1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cgld3d_Base_SDI1View message handlers
