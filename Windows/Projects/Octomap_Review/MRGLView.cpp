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

void	CMRGLView::TestOctomap()
{
	cout << "[Octomap Test]" << endl;
}