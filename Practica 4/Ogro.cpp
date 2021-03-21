#include "Ogro.h"

Ogro::Ogro() {
	ogro = NULL;
	ogro = glmReadOBJ("./Mallas/ogro.obj");

	glmUnitize(ogro);
	glmFacetNormals(ogro);
	glmVertexNormals(ogro, 90.0);
}

void Ogro::dibujarOgro() {
	glPushMatrix();
		glmDraw(ogro, GLM_SMOOTH | GLM_MATERIAL);
	glPopMatrix();
}

Ogro::~Ogro() {
	ogro = NULL;
}