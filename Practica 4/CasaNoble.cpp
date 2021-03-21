#include "CasaNoble.h"

CasaNoble::CasaNoble() {
	casa_noble = NULL;
	casa_noble = glmReadOBJ("./Mallas/casa_noble.obj");

	glmUnitize(casa_noble);
	glmFacetNormals(casa_noble);
	glmVertexNormals(casa_noble, 90.0);
}

void CasaNoble::dibujarCasaNoble() {
	glPushMatrix();
		glmDraw(casa_noble, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

CasaNoble::~CasaNoble() {
	casa_noble = NULL;
}