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
	//필요하면 재정의 해서 쓰고...
	DrawAxis();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	//INPUT
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3ub(255, 255, 0);
	for (int i = 0; i < 5; i++) {
		glVertex3d(points[i].x(), points[i].y(), 0.0);;
	}
	glEnd();

	//Result
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 255, 255);
	for (int i = 0; i < numCvPt; i++) {
		glVertex3d(result[i].x(), result[i].y(), 0.0);;
	}
	glEnd();

	glPointSize(4);
	glBegin(GL_POINTS);
	glColor3ub(255, 0, 0);
	for (int i = 0; i < numCvPt; i++) {
		glVertex3d(result[i].x(), result[i].y(), 0.0);;
	}
	glEnd();

	/*
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
	*/

	glPointSize(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}


void CMRGLView::Init()
{
	//OpenGL용 각종 변수 초기화
	CGLView::Init();
	m_vp.CameraDistance = 40.f;

	//CGAL 변수 초기화
	points[0] = Point_2(6, 5);
	points[1] = Point_2(0, 0);
	points[2] = Point_2(4, 1);
	points[3] = Point_2(10, 0);
	points[4] = Point_2(10, 10);

	ptr = CGAL::convex_hull_2(points, points + 5, result);
	numCvPt = ptr - result;

	/*
	//Getting Start #1
	p = Point_2(1, 1);
	q = Point_2(10, 10);
	s = Segment_2(p, q);
	m = Point_2(5, 4);

	mid = CGAL::midpoint(p, q);
	squared_distance = CGAL::squared_distance(p, q);
	orientation = CGAL::orientation(p, q, m);
	*/

}
