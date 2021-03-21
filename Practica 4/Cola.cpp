#include "Cola.h"

Cola::Cola() {
    for (int i = 0; i < 2; ++i) {
        objmodel_ptr[i] = NULL;
    }

    for (int i = 0; i < 2; ++i) {
        if (!objmodel_ptr[i]) {
            if(!i) objmodel_ptr[i] = glmReadOBJ("./Mallas/Susana.obj");
            else objmodel_ptr[i] = glmReadOBJ("./Mallas/dragon.obj");
            if (!objmodel_ptr) exit(0);

            glmUnitize(objmodel_ptr[i]);
            glmFacetNormals(objmodel_ptr[i]);
            glmVertexNormals(objmodel_ptr[i], 90.0);
        }
    }
}

void Cola::dibujarCola(int i) {
    glPushMatrix();
        glmDraw(objmodel_ptr[i], GLM_SMOOTH | GLM_MATERIAL);
    glPopMatrix();
}

Cola::~Cola() {
    for (int i = 0; i < 2; ++i) {
        objmodel_ptr[i] = NULL;
    }
}