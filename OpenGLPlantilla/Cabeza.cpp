#include "Cabeza.h"

Cabeza::Cabeza() {}

void Cabeza::dibujarCabeza() {
	glPushMatrix();
		glTranslatef(2.5, 4.6, 0.0);
		glRotatef((GLfloat)-68, 0.00001, 0.0, 0.1);
		glutSolidCube(1.3);
	glPopMatrix();
}

Cabeza::~Cabeza() {}