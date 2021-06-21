#include "Sancho.h"

Sancho::Sancho() {
	sancho = NULL;
	sancho = glmReadOBJ("./Mallas/gordi.obj");

	glmUnitize(sancho);
	glmFacetNormals(sancho);
	glmVertexNormals(sancho, 90.0);
}

void Sancho::dibujarSancho() {
	glPushMatrix();
	glmDraw(sancho, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

Sancho::~Sancho() {
	sancho = NULL;
}