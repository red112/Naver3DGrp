#pragma once

class pipeGeoMesh;
class pipeGeoRenderer
{
public:
	pipeGeoRenderer();
	~pipeGeoRenderer();

	static bool DrawPipeGeometry(pipeGeoMesh* pGeoMesh);

};