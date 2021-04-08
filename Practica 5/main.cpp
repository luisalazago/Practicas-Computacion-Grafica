//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "Caballo.h"
#include <iostream>
#include "glsl.h"
#include <time.h>

#define deltaX 0.01

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   Caballo rocinante;
   bool movX, movD, movA, movAbajo, rotarX, rotarD, rotarA, rotarAbajo, movZ1, movZ2;
   float camX, camY, camZ, rotX, rotY;

public:
	myWindow(){}

    void posCamara() {
        if (movX) camX += deltaX;
        else if (movD) camX -= deltaX;
        else if (movA) camY -= deltaX;
        else if (movAbajo) camY += deltaX;
        else if (movZ1) camZ += deltaX;
        else if (movZ2) camZ -= deltaX;
        else if (rotarX) rotX += deltaX;
        else if (rotarD) rotX -= deltaX;
        else if (rotarA) rotY -= deltaX;
        else if (rotarAbajo) rotY += deltaX;
    }

	virtual void OnRender(void)
	{
      double n, m, x;
      n = 2; m = 2; x = 0.5;
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!
      glPushMatrix();
      if (shader) shader->begin();
        posCamara();
        glTranslatef(camX, camY, camZ);
        glRotatef(0.0, rotX, rotY, 1.0);
        glPushMatrix();
            rocinante.dibujarCaballo();
        glPopMatrix();
      if (shader) shader->end();
      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
      else
      {
         ProgramObject = shader->GetProgramObject();
      }

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;
      
      // Objetos dentro del mundo
      rocinante = Caballo();

      DemoLight();
      movX = movD = movA = movAbajo = rotarX = rotarD = rotarA = rotarAbajo = movZ1 = movZ2 = false;
      camX = camY = camZ = rotX = rotY = 0;
	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{    
        std::cout << cAscii << std::endl;
        switch (cAscii) {
            case 27: 
                this->Close(); // Close Window!
                break;
            case 'a':
                movX = true;
                break;
            case 'd':
                movD = true;
                break;
            case 's':
                movAbajo = true;
                break;
            case 'w':
                movA = true;
                break;
            case 'u':
                rotarA = true;
                break;
            case 'h':
                rotarD = true;
                break;
            case 'j':
                rotarAbajo = true;
                break;
            case 'k':
                rotarD = true;
                break;
            case 'z':
                movZ1 = true;
                break;
            case 'x':
                movZ2 = true;
                break;
        }
        // std::cout << movX << std::endl;
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      switch (cAscii) {
        case 27:
            this->Close(); // Close Window!
            break;
        case 'a':
            movX = false;
            break;
        case 'd':
            movD = false;
            break;
        case 's':
            movAbajo = false;
            break;
        case 'w':
            movA = false;
            break;
        case 'u':
            rotarA = false;
            break;
        case 'h':
            rotarD = false;
            break;
        case 'j':
            rotarAbajo = false;
            break;
        case 'k':
            rotarD = false;
            break;
        case 'z':
            movZ1 = false;
            break;
        case 'x':
            movZ2 = false;
            break;
      }
      // std::cout << movX << std::endl;
      /*
      if (cAscii == 's')      // s: Shader
         shader->enable();*/
      if (cAscii == 'f') // f: Fixed Function
         shader->disable();
	}

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     /*
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     */
     // -------------------------------------------
     // Spotlight Attenuation
     /*
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     */
     
     // ------------------------------------------- 
     // Lighting parameters:
     
     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};/*
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};
     */
     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);/*
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
     */
     // -------------------------------------------
     // Material parameters:
     /*
     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
     */
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

