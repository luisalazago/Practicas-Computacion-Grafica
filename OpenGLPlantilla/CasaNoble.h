#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"
#include "glm/glm.h"

#pragma once
class CasaNoble {
	GLMmodel* casa_noble;
	public:
		CasaNoble();
		void dibujarCasaNoble();
		~CasaNoble();
};

