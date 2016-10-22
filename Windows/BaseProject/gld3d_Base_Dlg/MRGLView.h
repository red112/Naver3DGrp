#pragma once

using namespace std;

#include "glview.h"

class CMRGLView :
	public CGLView
{
public:
	CMRGLView(void);
	~CMRGLView(void);

	int		m_obj_id;

	void	DrawGL();

//	BOOL	OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
