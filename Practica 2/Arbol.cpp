#include "Arbol.h"

Arbol::Arbol() {}

void Arbol::dibujarArbol(float ax, float ay, float az) {
	glPushMatrix();
		
		glTranslatef(ax, ay, az);
		
		// Copa del árbol
		glPushMatrix();
			glTranslatef(0.0f, 1.0f, 0.0f);
			glutSolidSphere(1.0f, 20, 20);
		glPopMatrix();

		// Tronco del árbol
		glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glutSolidCylinder(0.5f, 1.0f, 20, 20);
		glPopMatrix();
	glPopMatrix();
}

Arbol::~Arbol(){}