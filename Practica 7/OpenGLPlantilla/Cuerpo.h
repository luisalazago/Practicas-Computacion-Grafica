#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>

#pragma once
class Cuerpo {
	public:
		Cuerpo();
		void dibujarCuerpo(double tam);
		~Cuerpo();
};

