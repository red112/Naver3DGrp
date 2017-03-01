#pragma once

#include "glm\glm.hpp"

class pipeGeoMesh;
class PGPipeBase
{
public:
	PGPipeBase();
	PGPipeBase(double out_rad);
	virtual ~PGPipeBase();

	void Init(double rad);

protected:
	double			m_out_rad;	//¿Ü°æ
	pipeGeoMesh*	m_pGeoMesh;

public:
	pipeGeoMesh*	GetNewMesh();
	pipeGeoMesh*	GetMesh();

};

class PGPipeStraight : public PGPipeBase
{
public:
	PGPipeStraight();
	PGPipeStraight(glm::dvec3 fromPt, glm::dvec3 toPt, double out_rad);
	virtual ~PGPipeStraight();

	void Init(glm::dvec3 fromPt, glm::dvec3 toPt, double out_rad);

protected:
	glm::dvec3	m_fromPt;
	glm::dvec3	m_toPt;
};
