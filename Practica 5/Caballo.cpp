#include "Caballo.h"

Caballo::Caballo() {
	caballo = NULL;
	caballo = glmReadOBJ("./Mallas/rocinante.obj");

	glmUnitize(caballo);
	glmFacetNormals(caballo);
	glmVertexNormals(caballo, 90.0);
}

void Caballo::dibujarCaballo() {
	glPushMatrix();
	glmDraw(caballo, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

Caballo::~Caballo() {
	caballo = NULL;
}