#include "stdafx.h"

#include "pipeGeoMaker.h"
#include "pipeGeoMesh.h"

pipeGeoMaker::pipeGeoMaker()
{

}

pipeGeoMaker::~pipeGeoMaker()
{

}

bool pipeGeoMaker::GenerateStraightPipe(PGPipeStraight* pStraightPipe)
{
	if (pStraightPipe == NULL)	return false;

	pipeGeoMesh* pMesh = pStraightPipe->GetNewMesh();

	//// Vertex
	//alloc
	pMesh->pVts = new pipeGeoMesh::pipeVertex[3];
	pMesh->nVtNum = 3;

	//
	pMesh->pVts[0].pos = glm::vec3(0.f, 0.f, 0.f);
	pMesh->pVts[1].pos = glm::vec3(150.f, 0.f, 0.f);
	pMesh->pVts[2].pos = glm::vec3(0.f, 150.f, 0.f);

	pMesh->pVts[0].nrm = glm::vec3(0.f, 0.f, 1.f);
	pMesh->pVts[1].nrm = glm::vec3(0.f, 0.f, 1.f);
	pMesh->pVts[2].nrm = glm::vec3(0.f, 0.f, 1.f);

	pMesh->pIdx = new unsigned short[3];
	pMesh->nFaceNum = 1;
	pMesh->pIdx[0] = 0;
	pMesh->pIdx[1] = 1;
	pMesh->pIdx[2] = 2;

	pMesh->rgb = glm::u8vec3(255, 0, 0);

	return true;
}
