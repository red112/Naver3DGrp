#pragma once

using namespace std;

#include "glview.h"

#include <iostream>
#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;

class CMRGLView :
	public CGLView
{
public:
	CMRGLView(void);
	~CMRGLView(void);


	Point_2 p;
	Point_2 q;
	Point_2 m;
	Point_2 mid;
	Segment_2 s;

	double		squared_distance;
	CGAL::Sign	orientation;

	//Initial setting
	void	Init();

	void	DrawGL();
};
