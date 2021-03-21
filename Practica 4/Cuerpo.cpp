#include "Cuerpo.h"

Cuerpo::Cuerpo() {}

void Cuerpo::dibujarCuerpo(double tam) {
	// Tronco
	glPushMatrix();
		glTranslatef(-2.0, 0.0f, 0.0f);
		glScalef(5.0, 2.0, 0.0);
		glutSolidCube(tam);
	glPopMatrix();

	// Cuello
	glPushMatrix();
		glTranslatef(-5.1, 0.2, 0.0);
		glRotatef((GLfloat)-15, 0.0, 0.0, 1.0);
		glScalef(3.0, 0.5, 0.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

Cuerpo::~Cuerpo() {}