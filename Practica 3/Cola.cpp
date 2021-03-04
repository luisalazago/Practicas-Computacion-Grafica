#include "Cola.h"

#define numSeg 7

Cola::Cola() {}

void Cola::dibujarCola() {
    glTranslatef(-0.5, 0.0, 0.0);
    glRotatef((GLfloat)20, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glPushMatrix();
        glScalef(1.0, 0.4, 0.5);
        glutSolidCube(1.0);
    glPopMatrix();

    int angulo = 20;
    for (int i = 0; i < numSeg; ++i) {
        glTranslatef(0.5, 0.0, 0.0);
        if (i == (numSeg - 1)) {
            glRotatef((GLfloat)10, 0.0, 0.0, 1.0);
            glTranslatef(0.5, 0.0, 0.0);
            glPushMatrix();
                glScalef(0.4, 0.4, 0.5);
                glutSolidDodecahedron();
            glPopMatrix();
            
            glTranslatef(0.5, 0.0, 0.0);
            glRotatef((GLfloat)-85, 0.0, 0.0, 1.0);
            glTranslatef(-0.1, 0.0, 0.7);
            glPushMatrix();
                glScalef(0.4, 0.4, 0.5);
                glBegin(GL_TRIANGLES);
                    glVertex3f(0.5f, 0.0f, 0.0f);
                    glVertex3f(-0.5f, 0.0f, 0.0f);
                    glVertex3f(0.0f, 2.5f, 0.0f);
                glEnd();
            glPopMatrix();
        }
        else {
            glRotatef((GLfloat)angulo, 0.0, 0.0, 1.0);
            glTranslatef(0.5, 0.0, 0.0);
            glPushMatrix();
                glScalef(1.0, 0.4, 0.5);
                glutSolidCube(1.0);
            glPopMatrix();
        }
        angulo += 5;
    }
}

Cola::~Cola() {}