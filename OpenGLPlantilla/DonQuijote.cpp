#include "DonQuijote.h"

DonQuijote::DonQuijote() {
	donQuijote = NULL;
	donQuijote = glmReadOBJ("./Mallas/objBook.obj");

	glmUnitize(donQuijote);
	glmFacetNormals(donQuijote);
	glmVertexNormals(donQuijote, 90.0);
}

void DonQuijote::dibujarDonQuijote() {
	glPushMatrix();
		glmDraw(donQuijote, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
}

DonQuijote::~DonQuijote() {
	donQuijote = NULL;
}