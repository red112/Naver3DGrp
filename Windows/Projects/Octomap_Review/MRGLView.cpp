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

void	CMRGLView::TestOctomap()
{
	cout << "[Octomap Test]" << endl;
}