#include "Tetera.h"

Tetera::Tetera() {}

void Tetera::dibujarTetera(float x, float y, float z) {
	glPushMatrix();

		glTranslatef(x, y, z);

		glPushMatrix();
			glutSolidTeapot(1.0f);
		glPopMatrix();
	glPopMatrix();
}

Tetera::~Tetera() {}
