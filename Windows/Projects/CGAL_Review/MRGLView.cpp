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
	//CGLView::DrawGL();
	//필요하면 재정의 해서 쓰고...
	DrawAxis();

	glDisable(GL_LIGHTING);
	glPointSize(4);

	switch(orientation)
	{
	case CGAL::COLLINEAR:	glColor3ub(255, 255, 0);		break;
	case CGAL::LEFT_TURN:	glColor3ub(255, 0, 255);		break;
	case CGAL::RIGHT_TURN:	glColor3ub(0, 255, 255);		break;
	}

	glBegin(GL_LINE_STRIP);
	glVertex3d(p.x(), p.y(), 0.0);
	glVertex3d(q.x(), q.y(), 0.0);
	glVertex3d(m.x(), m.y(), 0.0);
	glEnd();


	glBegin(GL_POINTS);
	glColor3ub(255, 0, 0);		glVertex3d(p.x(), p.y(), 0.0);
	glColor3ub(0,255, 0);		glVertex3d(q.x(), q.y(), 0.0);
	glColor3ub(0, 0, 255);		glVertex3d(m.x(), m.y(), 0.0);
	glColor3ub(255, 255, 255);	glVertex3d(mid.x(), mid.y(), 0.0);
	glEnd();

	glPointSize(1);
	glEnable(GL_LIGHTING);
}


void CMRGLView::Init()
{
	CGLView::Init();

	p = Point_2(1, 1);
	q = Point_2(10, 10);
	s = Segment_2(p, q);
	m = Point_2(5, 9);

	mid = CGAL::midpoint(p, q);
	squared_distance = CGAL::squared_distance(p, q);
	orientation = CGAL::orientation(p, q, m);

	m_vp.CameraDistance = 40.f;

	/*
	case CGAL::COLLINEAR:
		std::cout << "are collinear\n";
		break;
	case CGAL::LEFT_TURN:
		std::cout << "make a left turn\n";
		break;
	case CGAL::RIGHT_TURN:
		std::cout << "make a right turn\n";
		break;
	}
	std::cout << " midpoint(p,q) = " << CGAL::midpoint(p, q) << std::endl;
	*/
}
