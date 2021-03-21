#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"
#include "glm/glm.h"

#pragma once
class Cola {
	GLMmodel* objmodel_ptr[2];
	public:
		Cola();
		void dibujarCola(int i);
		~Cola();
};

