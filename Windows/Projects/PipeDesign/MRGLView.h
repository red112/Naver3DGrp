#pragma once

using namespace std;

#include "glview.h"

#include "pipeGeo\pipeGeoType.h"

class CMRGLView :
	public CGLView
{
public:
	CMRGLView(void);
	~CMRGLView(void);

	void	DrawGL();

	PGPipeStraight	m_StraightPipe;

//	BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
