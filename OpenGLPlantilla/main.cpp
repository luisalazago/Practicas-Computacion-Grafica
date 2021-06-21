//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "Caballo.h"
#include "DonQuijote.h"
#include "Sancho.h"
#include "Plano.h"
#include "CasaNoble.h"
#include "CasaPobre.h"
#include "Molino.h"
#include "Ogro.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include <FreeImage.h>

#define deltaX 0.01
#define deltaRX 0.01
#define deltaAlfa 0.1

//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   cwc::glShader* shaderT;
   GLuint ProgramObject;
   GLuint textId;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   Caballo rocinante;
   DonQuijote donQuijote;
   Sancho sancho;
   Plano plano;
   CasaNoble casa_noble;
   CasaPobre casa_pobre;
   Molino molino;
   Ogro ogro;
   bool movX, movD, movA, movAbajo, movZ1, movZ2;
   float camX, camY, camZ;
   bool rotarDer, rotarIzq, rotarUp, rotarDown;
   float ejex, ejey, ejez;
   float alfa;
   bool movRI, movRD, movZfrente, movZatras;
   float movRocX, movRocZ;
   GLuint texid;

public:
	myWindow(){}

    void posCamara() {
        if (movX) camX += deltaX;
        else if (movD) camX -= deltaX;
        else if (movA) camY -= deltaX;
        else if (movAbajo) camY += deltaX;
        else if (movZ1) camZ += deltaX;
        else if (movZ2) camZ -= deltaX;
    }

    void posRoci() {
        if (movRI) movRocX -= deltaRX;
        else if (movRD) movRocX += deltaRX;
        else if (movZfrente) movRocZ += deltaRX;
        else if (movZatras) movRocZ -= deltaRX;
    }

    void posVision() {
        if (rotarDer) {
            ejey++;
            alfa = alfa + deltaAlfa < 360 ? alfa + deltaAlfa : 0;
        }
        else if (rotarIzq) {
            ejey++;
            alfa = alfa - deltaAlfa >= 0 ? alfa - deltaAlfa : 360 - deltaAlfa;
        }
        if (rotarUp) {
            ejex++;
            alfa = alfa + deltaAlfa < 360 ? alfa + deltaAlfa : 0;
        }
        else if (rotarDown) {
            ejex++;
            alfa = alfa - deltaAlfa >= 0 ? alfa - deltaAlfa : 360 - deltaAlfa;
        }
    }

    void initialize_textures(void)
    {
        int w, h;
        GLubyte* data = 0;
        //data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
        //std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;
        //dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage
        
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./Mallas/libro.jpg", 0),
            "./Mallas/libro.jpg");
        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

	virtual void OnRender(void)
	{
      double n, m, x;
      n = 2; m = 2; x = 0.5;
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!
      glPushMatrix();
      posCamara();
      posVision();
      posRoci();
      glTranslatef(camX, camY, camZ);
      glRotatef(alfa, ejex, ejey, ejez);
      if (shader) shader->begin();
          glTranslatef(2.0f, 0.0f, -1.5f);

          //Casas nobles

          //La casa de don quijote de la mancha
          glPushMatrix();
            casa_noble.dibujarCasaNoble();
          glPopMatrix();

          //Casa noble del frente de don quijote
          glPushMatrix();
              glTranslatef(-1 * n, 0, 0);
              glRotatef(180, 0, 1, 0);
              casa_noble.dibujarCasaNoble();
          glPopMatrix();

          //Casas pobres

          glPushMatrix();
              //Casa pobre 1
              glTranslatef((-1 * n) / 2, 0, 0/*(-1 * m)*/);
              /*glPushMatrix();

              glPopMatrix();*/
              glTranslatef(0, 0, (-1 * m));
              for (int i = 0; i < 2; ++i) {
                  glPushMatrix();
                      glTranslatef(0, 0, -1 * (i * 1));
                      glScalef(0.25, 0.25, 0.25);
                      glPushMatrix();
                          glTranslatef(2 * n, -0.4, 0.0);
                          glRotatef(45, 0, 1, 0);
                          casa_pobre.dibujarCasaPobre();
                      glPopMatrix();

                      glPushMatrix();
                          glTranslatef(-2 * n, -0.4, 0.0);
                          glRotatef(180, 0, 1, 0);
                          casa_pobre.dibujarCasaPobre();
                      glPopMatrix();
                  glPopMatrix();
              }
          glPopMatrix();

          // Caballo
          glPushMatrix();
              glTranslatef(movRocX, -0.2, movRocZ);
              glScalef(0.25, 0.25, 0.25);
              rocinante.dibujarCaballo();
          glPopMatrix();
          //Sector 3 ubicación molinos

          glPushMatrix();
              glTranslatef(((-1 * n) / 2), 0, (-1 * m) - 2);
              // Plano
              glPushMatrix();
                glTranslatef(0.0, ((-1 * m) / 6), 0.0);
                glScalef(10.0, 0.01, 20.0);
                plano.dibujarPlano(1.0);
              glPopMatrix();
              // Sancho Panza
              glPushMatrix();
                glTranslatef(-0.1, -0.238, 0.7);
                glScalef(0.1, 0.1, 0.1);
                sancho.dibujarSancho();
              glPopMatrix();
              //Molinos
              glPushMatrix();
                  glTranslatef(-x, 0, 0);
                  for (int i = 0; i < 2; ++i) {
                      glPushMatrix();
                          glTranslatef(0, 0, -1 * (i * 2));
                          glScalef(0.33, 0.33, 0.33);
                          molino.dibujarMolino();
                      glPopMatrix();
                  }
              glPopMatrix();

              //Ogros
              glPushMatrix();
                  glTranslatef(x, 0, 0);
                  for (int i = 0; i < 2; ++i) {
                      glPushMatrix();
                          glTranslatef(0, -0.07, -1 * (i * 2));
                          glScalef(0.33, 0.33, 0.33);
                          ogro.dibujarOgro();
                      glPopMatrix();
                  }
              glPopMatrix();
          glPopMatrix();
      if (shader) shader->end();

      if (shaderT) shaderT->begin();
          // Don Quijote
          glPushMatrix();
            glTranslatef(movRocX, -0.08, movRocZ);
            glRotatef(90, 1.0, 0.0, 0.0);
            glScalef(0.06, 0.06, 0.06);
            glBindTexture(GL_TEXTURE_2D, texid);
            donQuijote.dibujarDonQuijote();
          glPopMatrix();
      if (shaderT) shaderT->end();
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

        shaderT = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
        if (shaderT == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shaderT->GetProgramObject();
        }

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;
      
      // Objetos dentro del mundo
      rocinante = Caballo();
      donQuijote = DonQuijote();
      sancho = Sancho();
      plano = Plano();
      casa_pobre = CasaPobre();
      casa_noble = CasaNoble();
      molino = Molino();
      ogro = Ogro();

      initialize_textures();

      DemoLight();
      movX = movD = movA = movAbajo = movZ1 = movZ2 = false;
      camX = camY = camZ = 0;
      rotarDer = rotarIzq = rotarUp = rotarDown = false;
      ejex = ejey = ejez = alfa = 0;
      movRI = movRD = movZfrente = movZatras = false;
      movRocX = -1;
      movRocZ = 3;
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
        std::cout << nKey << std::endl;
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
        case 'z':
            movZ1 = true;
            break;
        case 'x':
            movZ2 = true;
            break;
            //Vision rotacion
        case 'i':
            rotarUp = true;
            break;
        case 'k':
            rotarDown = true;
            break;
        case 'j':
            rotarIzq = true;
            break;
        case 'l':
            rotarDer = true;
            break;
        case 'r':
            ejex = 0;
            ejey = 0;
            ejez = 0;
            alfa = 0;
            break;
        }
        switch (nKey) {
            //Mov rocinanate
        case 100:
            movRI = true;
            break;
        case 102:
            movRD = true;
            break;
        case 103:
            movZfrente = true;
            break;
        case 101:
            movZatras = true;
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
        case 'z':
            movZ1 = false;
            break;
        case 'x':
            movZ2 = false;
            break;
            //Vision rotacion
        case 'i':
            rotarUp = false;
            break;
        case 'k':
            rotarDown = false;
            break;
        case 'j':
            rotarIzq = false;
            break;
        case 'l':
            rotarDer = false;
            break;
        }
        switch (nKey) {
            //Mov rocinanate
        case 100:
            movRI = false;
            break;
        case 102:
            movRD = false;
            break;
        case 103:
            movZfrente = false;
            break;
        case 101:
            movZatras = false;
            break;
        }
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

