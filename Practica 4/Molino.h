#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"
#include "glm/glm.h"

#pragma once
class Molino {
	GLMmodel* molino;
public:
	Molino();
	void dibujarMolino();
	~Molino();
};
