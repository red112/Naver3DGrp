#pragma once

#include <glm/glm.hpp>

class pipeGeoMesh
{
public:
	struct pipeVertex
	{
		glm::vec3	pos;
		glm::vec3	nrm;
	};

	pipeGeoMesh() 
	{
		pVts = 0;
		pIdx = 0;
		nVtNum = nFaceNum = 0;
	};

	virtual ~pipeGeoMesh()
	{
		if (pVts)	delete pVts;
		pVts = 0;
		if (pIdx)	delete pIdx;
		pIdx = 0;
	};

	int			nVtNum;
	pipeVertex* pVts;

	int			nFaceNum;
	unsigned short* pIdx;

	glm::u8vec3	rgb;
};
