#pragma once

using namespace std;

#include "glview.h"

#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

/*
#include <CGAL/Simple_cartesian.h>
typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point_2;
typedef Kernel::Segment_2 Segment_2;
*/

class CMRGLView :
	public CGLView
{
public:
	CMRGLView(void);
	~CMRGLView(void);

	Point_2 points[5];
	Point_2 result[5];
	Point_2 *ptr;
	int		numCvPt;

/*
//Getting Start #1
	Point_2 p;
	Point_2 q;
	Point_2 m;
	Point_2 mid;
	Segment_2 s;
	double		squared_distance;
	CGAL::Sign	orientation;
	*/
	//Initial setting
	void	Init();

	void	DrawGL();
};
