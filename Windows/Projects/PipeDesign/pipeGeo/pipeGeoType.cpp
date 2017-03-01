#include "stdafx.h"

#include "pipeGeoType.h"
#include "pipeGeoMesh.h"

PGPipeBase::PGPipeBase()
{
	m_out_rad = 0.0;
	m_pGeoMesh = 0;
}


PGPipeBase::PGPipeBase(double out_rad)
{
	m_out_rad = out_rad;
	m_pGeoMesh = 0;
}

PGPipeBase::~PGPipeBase()
{
	if (m_pGeoMesh)	delete m_pGeoMesh;
	m_pGeoMesh = 0;
}


void PGPipeBase::Init(double rad)
{
	m_out_rad = rad;
	m_pGeoMesh = 0;
}

pipeGeoMesh*	PGPipeBase::GetMesh()
{
	return m_pGeoMesh;
}


pipeGeoMesh*	PGPipeBase::GetNewMesh()
{
	if (m_pGeoMesh)	delete m_pGeoMesh;
	m_pGeoMesh = new pipeGeoMesh;
	return m_pGeoMesh;
}

/////////////////////////////////////////////////////
PGPipeStraight::PGPipeStraight()
		: PGPipeBase()
{
}

PGPipeStraight::PGPipeStraight(glm::dvec3 fromPt, glm::dvec3 toPt, double out_rad)
	: PGPipeBase(out_rad)
{
	m_fromPt = fromPt;
	m_toPt = toPt;
}
PGPipeStraight::~PGPipeStraight()
{
}

void PGPipeStraight::Init(glm::dvec3 fromPt, glm::dvec3 toPt, double out_rad)
{
	PGPipeBase::Init(out_rad);
	m_fromPt = fromPt;
	m_toPt = toPt;
}