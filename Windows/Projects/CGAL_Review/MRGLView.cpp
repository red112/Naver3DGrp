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
	//��� ���� �׳� ���� ���� ������, 
	CGLView::DrawGL();
	//�ʿ��ϸ� ������ �ؼ� ����...

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