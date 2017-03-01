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
	//요걸 쓰면 그냥 빨간 구만 나오고, 
	CGLView::DrawGL();
	//필요하면 재정의 해서 쓰고...

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