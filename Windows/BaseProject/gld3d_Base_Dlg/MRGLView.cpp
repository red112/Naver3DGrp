#include "StdAfx.h"
#include "MRGLView.h"

CMRGLView::CMRGLView(void)
{

}

CMRGLView::~CMRGLView(void)
{

}


void CMRGLView::DrawGL()
{
	//요걸 쓰면 그냥 빨간 구만 나오고, 
	CGLView::DrawGL();
	//필요하면 재정의 해서 쓰고...

}
/*
BOOL CMRGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if(zDelta>0)	m_vp.CameraDistance *= 1.005f;
	else			m_vp.CameraDistance *= 0.995f;


	Invalidate(FALSE);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
*/