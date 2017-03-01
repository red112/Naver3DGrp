
#include "stdafx.h"

#include "pipeGeoRenderer.h"

#include "pipeGeoMesh.h"
#include <GL/GL.h>

pipeGeoRenderer::pipeGeoRenderer()
{
}

pipeGeoRenderer::~pipeGeoRenderer()
{

}

bool pipeGeoRenderer::DrawPipeGeometry(pipeGeoMesh* pGeoMesh)
{
	if (pGeoMesh->pVts == NULL || pGeoMesh->pIdx == NULL)	return false;

//	glColor3b(pGeoMesh->rgb.r, pGeoMesh->rgb.g, pGeoMesh->rgb.b);

	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glColor3b(255,255,0);

//	glVertexPointer(3, GL_FLOAT, sizeof(pipeGeoMesh::pipeVertex), &(pGeoMesh->pVts[0].pos));
//	glNormalPointer(GL_FLOAT, sizeof(pipeGeoMesh::pipeVertex), &(pGeoMesh->pVts[0].nrm));
//	glDrawElements(GL_TRIANGLES, pGeoMesh->nFaceNum*3, GL_UNSIGNED_SHORT, &(pGeoMesh->pIdx));

	glBegin(GL_TRIANGLES);
	glNormal3f(0.f, 0.f, 1.f);

	glVertex3f(pGeoMesh->pVts[0].pos.x, pGeoMesh->pVts[0].pos.y, pGeoMesh->pVts[0].pos.z);
	glVertex3f(pGeoMesh->pVts[1].pos.x, pGeoMesh->pVts[1].pos.y, pGeoMesh->pVts[1].pos.z);
	glVertex3f(pGeoMesh->pVts[2].pos.x, pGeoMesh->pVts[2].pos.y, pGeoMesh->pVts[2].pos.z);

	glEnd();

	return true;
}


