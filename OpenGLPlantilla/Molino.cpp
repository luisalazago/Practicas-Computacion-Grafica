#include "Molino.h"

Molino::Molino() {
	molino = NULL;
	molino = glmReadOBJ("./Mallas/molino.obj");

	glmUnitize(molino);
	glmFacetNormals(molino);
	glmVertexNormals(molino, 90.0);
}

void Molino::dibujarMolino() {
	glPushMatrix();
		glmDraw(molino, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

Molino::~Molino() {
	molino = NULL;
}