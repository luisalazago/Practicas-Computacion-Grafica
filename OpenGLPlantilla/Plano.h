#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"
#include "glm/glm.h"

#pragma once
class Plano {
	Plano* plano;
public:
	Plano();
	void dibujarPlano(float tam);
	~Plano();
};
