#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "gl/glut.h"   // - An interface and windows
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions

#define LIGHT_VAL 0.01;
Stars stars;
float light_anim=0.0;
bool plus = true;
float cx=0.0f,cy=0.0f,cz=0.0f;

Stars::Stars(){
    srand(time(NULL));
    numOfStars=(rand() % (MAX_STARS - MIN_STARS + 1)) + MIN_STARS;
    starsArray = new Star[numOfStars];

    for (int i = 0; i < numOfStars; i++) {
        starsArray[i].radius = (rand() % 10 + 90) * 0.001f;
        starsArray[i].x = rand() % 60 - 30;
        starsArray[i].y = rand() %  60 -30;
        starsArray[i].z = rand() % 50 - 25;
        starsArray[i].transparecy = 0.0;
        printf("%f\n",starsArray[i].radius);
    }

}
void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
        case 'q' : exit(0);
            break;
        case 'w' : cy+=0.5f;
            break;
        case 's' : cy-=0.5f;
            break;
        case 'a' : cx+=0.5f;
            break;
        case 'd' : cx-=0.5f;
            break;
        default : break;
	}

	glutPostRedisplay();

}


Stars::~Stars() {
    delete[] starsArray;
    starsArray = NULL;
}

void Stars::DrawStars(){
    float x,y,z,t,r;
    printf("%d\n", numOfStars);
    for(int i=0;i<numOfStars;i++){
      glPushMatrix();
      x=starsArray[i].x;
      y=starsArray[i].y;
      z=starsArray[i].z;
      t=starsArray[i].transparecy;
      r=starsArray[i].radius;
      printf("%f %f %f %f\n", x, y, z,r);
      glTranslatef(x, y, z);
      glTranslatef(x, y, z);
      glColor3f(255, 255, 255);							   // Set drawing colour
      glutSolidSphere(r, 30, 23);							   // Draw a built-in primitive
      glColor4f(255, 255, 255, light_anim);					   // Set drawing colour and transparency
      glutSolidSphere(r + r * light_anim, 30, 23);							   // Draw a built-in primitive
      glPopMatrix();
    }
}


void createSun() {
  //Sun creation
  glTranslatef(0,0,-100);

  glRotatef(cx, 0,1,0);
  glRotatef(cy, 1,0,0);
  glColor3f(1.0, 0.5, 0.2);							   // Set drawing colour
  glutSolidSphere(15.0, 30, 23);							   // Draw a built-in primitive


  glColor4f(1.0, 0.5, 0.2, light_anim);					   // Set drawing colour and transparency
  glutSolidSphere(15.0 + 5.0 * light_anim, 30, 23);							   // Draw a built-in primitive
}

void Render()
{
  static float deg=0;
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  createSun();

  //Random stars creation
  stars.DrawStars();
  glutSwapBuffers();             // All drawing commands applied to the
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h)
{
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0,0,w,h);

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}

void Idle()
{
    if(light_anim>=1.0){
        plus=false;
        //light_anim-=LIGHT_VAL;
    }else if(light_anim <= 0.0) {
         plus = true;
         //light_anim += LIGHT_VAL;
    }
    if (plus) {
        light_anim+=LIGHT_VAL;
    } else if (!plus) {
        light_anim -= LIGHT_VAL;
    }
    glutPostRedisplay();
}

void Setup()  // TOUCH IT !!
{
	//Parameter handling
	glShadeModel (GL_SMOOTH);

	//(02)
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
//	glClearDepth(1);

	// (06) // polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	//Set up light source
	GLfloat light_position[] = { 0.0, 0.0, -50.0, 0.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };


	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );

	//(05)
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,64);
	/*

	//(06) Material Parameters
	//(06a) for Gold
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[4];
	specref[0] = 0.247; specref[1] = 0.225; specref[2] = 0.065; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
	specref[0] = 0.346; specref[1] = 0.314; specref[2] = 0.090; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
	specref[0] = 0.797; specref[1] = 0.724; specref[2] = 0.208; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMaterialf(GL_FRONT,GL_SHININESS,83.2);
	*/

	//(06b) for Ruby
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[4];
	specref[0] = 0.175; specref[1] = 0.012; specref[2] = 0.012; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
	specref[0] = 0.614; specref[1] = 0.041; specref[2] = 0.041; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
	specref[0] = 0.728; specref[1] = 0.308; specref[2] = 0.308; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMaterialf(GL_FRONT,GL_SHININESS,76.8);
	*/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// (04)
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	//(03)
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);



	//(01) BLENDING
   glEnable(GL_BLEND);
                  //incoming //  // stored //
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

