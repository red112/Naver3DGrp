#include "StdAfx.h"
#include "MRGLView.h"

#include "pipeGeo\pipeGeoMaker.h"
#include "pipeGeo\pipeGeoRenderer.h"

CMRGLView::CMRGLView(void)
{
	glm::dvec3 fromPt(0.0, 0.0, 0.0);
	glm::dvec3 toPt(10.0, 10.0, 10.0);
	double rad = 2.0;

	m_StraightPipe.Init(fromPt, toPt, rad);

	bool bResult = pipeGeoMaker::GenerateStraightPipe(&m_StraightPipe);

}

CMRGLView::~CMRGLView(void)
{

}


void CMRGLView::DrawGL()
{
	//��� ���� �׳� ���� ���� ������, 
	CGLView::DrawGL();
	//�ʿ��ϸ� ������ �ؼ� ����...

	pipeGeoMesh* pMesh = m_StraightPipe.GetMesh();
	if (pMesh)	pipeGeoRenderer::DrawPipeGeometry(pMesh);

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