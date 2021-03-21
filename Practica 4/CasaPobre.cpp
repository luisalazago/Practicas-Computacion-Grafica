#include "CasaPobre.h"

CasaPobre::CasaPobre() {
	casa_pobre = NULL;
	casa_pobre = glmReadOBJ("./Mallas/casa_pobre.obj");

	glmUnitize(casa_pobre);
	glmFacetNormals(casa_pobre);
	glmVertexNormals(casa_pobre, 90.0);
}

void CasaPobre::dibujarCasaPobre() {
	glPushMatrix();
		glmDraw(casa_pobre, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

CasaPobre::~CasaPobre() {
	casa_pobre = NULL;
}