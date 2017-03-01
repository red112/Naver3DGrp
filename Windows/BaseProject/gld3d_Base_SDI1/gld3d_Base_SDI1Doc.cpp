
// gld3d_Base_SDI1Doc.cpp : implementation of the Cgld3d_Base_SDI1Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "gld3d_Base_SDI1.h"
#endif

#include "gld3d_Base_SDI1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cgld3d_Base_SDI1Doc

IMPLEMENT_DYNCREATE(Cgld3d_Base_SDI1Doc, CDocument)

BEGIN_MESSAGE_MAP(Cgld3d_Base_SDI1Doc, CDocument)
END_MESSAGE_MAP()


// Cgld3d_Base_SDI1Doc construction/destruction

Cgld3d_Base_SDI1Doc::Cgld3d_Base_SDI1Doc()
{
	// TODO: add one-time construction code here

}

Cgld3d_Base_SDI1Doc::~Cgld3d_Base_SDI1Doc()
{
}

BOOL Cgld3d_Base_SDI1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cgld3d_Base_SDI1Doc serialization

void Cgld3d_Base_SDI1Doc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void Cgld3d_Base_SDI1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void Cgld3d_Base_SDI1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Cgld3d_Base_SDI1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cgld3d_Base_SDI1Doc diagnostics

#ifdef _DEBUG
void Cgld3d_Base_SDI1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cgld3d_Base_SDI1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cgld3d_Base_SDI1Doc commands
