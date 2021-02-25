#include "Decahedro.h"

Decahedro::Decahedro() {}

void Decahedro::dibujarDecahedro(float x, float y, float z) {
	glPushMatrix();
		
		glTranslatef(x, y, z);
		glRotatef(90, 0.0f, 0.0f, 1.0f);

		glPushMatrix();
			glutSolidDodecahedron();
		glPopMatrix();
	glPopMatrix();
}

Decahedro::~Decahedro() {}