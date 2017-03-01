#pragma once

#include "pipeGeoType.h"
class pipeGeoMesh;
class PGPipeStraight;
class pipeGeoMaker
{
public:
	pipeGeoMaker();
	~pipeGeoMaker();

	static bool GenerateStraightPipe(PGPipeStraight* pStraightPipe);

};
