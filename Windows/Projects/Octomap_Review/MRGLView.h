#pragma once

using namespace std;

#include "glview.h"

#include <octomap/octomap.h>
#include <octomap/OcTree.h>

using namespace std;
using namespace octomap;


class CMRGLView :
	public CGLView
{
public:
	CMRGLView(void);
	~CMRGLView(void);

	int		m_obj_id;

	void	DrawGL();


	void	TestOctomap();
};
