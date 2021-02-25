#include "Triangulo.h"

Triangulo::Triangulo() {}

void Triangulo::dibujarTriangulo(float x, float y, float z) {
	glPushMatrix();
		
		glTranslatef(x, y, z);

		// Creación del Triangulo.
		glPushMatrix();
			glBegin(GL_TRIANGLES);
				glVertex3f(1.5f, 0.0f, 0.0f);
				glVertex3f(-1.5f, 0.0f, 0.0f);
				glVertex3f(0.0f, 2.3f, 0.0f);
			glEnd();
		glPopMatrix();
	glPopMatrix();
}

Triangulo::~Triangulo() {}