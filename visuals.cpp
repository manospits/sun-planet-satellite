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
model md;
static float light_anim = 0.0;
static bool plus = true;
static bool pause_anim = false;
static float cx = 0.0f, cy = 0.0f, planet_c=0.0f,planet_s=0.0f;

void ReadFile();
void DisplayModel();

    Stars::Stars(){
    srand(time(NULL));
    numOfStars=(rand() % (MAX_STARS - MIN_STARS + 1)) + MIN_STARS;
    starsArray = new Star[numOfStars];

    for (int i = 0; i < numOfStars; i++) {
        // starsArray[i].radius = (rand() % 10 + 90) * 0.001f;
        starsArray[i].radius = 0.2;
        starsArray[i].x = rand() % 201 - 100; // range between [-100, 100]
        starsArray[i].y = rand() % 201 - 100; // range between [-100, 100]
        starsArray[i].z = rand() % 201 - 300; //range between [-300, -100]
    }

}

Stars::~Stars() {
    delete[] starsArray;
    starsArray = NULL;
}

void Stars::DrawStars(){
    float x,y,z,t,r;
    //printf("%d\n", numOfStars);
    for(int i=0;i<numOfStars;i++){
      glPushMatrix();
      x = starsArray[i].x;
      y = starsArray[i].y;
      z = starsArray[i].z;
      r = starsArray[i].radius;
    //   printf("%f %f %f %f\n", x, y, z,r);
      glTranslatef(x, y, z);
      glColor4f(1.0, 1.0, 1.0, 1.0);							   // Set drawing colour
      glutSolidSphere(r, 30, 23);							   // Draw a built-in primitive
      glColor4f(1.0, 1.0, 1.0, light_anim);					   // Set drawing colour and transparency
      glutSolidSphere(r + r * light_anim, 30, 23);							   // Draw a built-in primitive
      glPopMatrix();
    }
}


void createSun() {
  //Sun creation

  glPushMatrix();
  glTranslatef(0,0,-200);
  glColor4f(1.0, 1.0, 0.4, 1.0);							   // Set drawing colour
  glutSolidSphere(15.0, 30, 23);							   // Draw a built-in primitive

  glColor4f(1.0, 1.0, 0.4, light_anim);					   // Set drawing colour and transparency
  glutSolidSphere(15.0 + 5.0 * light_anim, 30, 23);							   // Draw a built-in primitive
  glPopMatrix();
}
void DrawSatellite(){
  glPushMatrix();
  glTranslatef(0,0,-200);
  glRotatef(planet_s,1,0,0);
  glTranslatef(0,0,187);
  glTranslatef(-50,13,-200);
  glColor3f(0.5,0.0, 0.9);							   // Set drawing colour
  glScalef(0.005,0.005,0.005);
  DisplayModel();
  glPopMatrix();

}

void DrawPlanet(){
  glPushMatrix();
  glTranslatef(0,0,-200);
  glRotatef(planet_c,0,1,0);
  glTranslatef(0,0,150);
  DrawSatellite();
  glTranslatef(-50,0,-200);
  glColor3f(0.1, 1.0, 0.4);							   // Set drawing colour
  glScalef(0.015,0.015,0.015);
  DisplayModel();
  glPopMatrix();

}
void Render()
{
  static float deg=0;
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0, -200);
  glRotatef(cx, 0,1,0);
  glRotatef(cy, 1,0,0);
  glTranslatef(0,0, 200);

  createSun();
  DrawPlanet();
  stars.DrawStars();

  glTranslatef(0, 0, 200);
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

void Idle() {

    if (! pause_anim) {
        if (light_anim >= 1.0){
            plus = false;
        } else if (light_anim <= 0.0) {
             plus = true;
        }

        if (plus) {
            light_anim += LIGHT_VAL;
        } else if (!plus) {
            light_anim -= LIGHT_VAL;
        }
    }
    planet_c+=1.5;
    planet_s+=3;
    glutPostRedisplay();
}

void Keyboard(unsigned char key,int x,int y) {
	switch(key)
	{
        case 'p' :
            pause_anim = (pause_anim == true) ? false : true;
            break;
        case 'q' : exit(0);
            break;
        case 'w' : cy += 0.5f;
            break;
        case 's' : cy -= 0.5f;
            break;
        case 'a' : cx += 0.5f;
            break;
        case 'd' : cx -= 0.5f;
            break;
        default : break;
	}

	glutPostRedisplay();

}

void Setup() {
    ReadFile();
	glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

	//Set up light source
	GLfloat light_position[] = { 0.0, 0.0, -5.0, 0.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };


	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
    //glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight );

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}

void ReadFile()
{
    FILE * pFile;
    char buf[256];
    pFile = fopen ("planet.obj","r");
    int i=0,j=0,k=0;
    while(!feof(pFile)){
        fscanf(pFile,"%s  ",buf);
        if(strcmp(buf,"v")==0){
            fscanf(pFile,"%f %f %f ",&md.obj_points[i].x,&md.obj_points[i].y,&md.obj_points[i].z);
            i++;
        }
        else if (strcmp(buf,"f")==0) {
            fscanf(pFile,"%d//%d %d//%d %d//%d ",&md.obj_faces[j].v[0],&md.obj_faces[j].vn[0],&md.obj_faces[j].v[1],&md.obj_faces[j].vn[1],&md.obj_faces[j].v[2],&md.obj_faces[j].vn[2]);
            j++;
        }
        else if(strcmp(buf,"vn")==0){
            fscanf(pFile,"%f %f %f ",&md.vn[k].x,&md.vn[k].y,&md.vn[k].z);
            k++;
        }
    }
    fclose(pFile);
}

void DisplayModel(){
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for(int i=0;i<FNUM;i++){
        glVertex3f(md.obj_points[md.obj_faces[i].vn[0]-1].x,md.obj_points[md.obj_faces[i].vn[0]-1].y,md.obj_points[md.obj_faces[i].vn[0]-1].z);
        glVertex3f(md.obj_points[md.obj_faces[i].vn[1]-1].x,md.obj_points[md.obj_faces[i].vn[1]-1].y,md.obj_points[md.obj_faces[i].vn[1]-1].z);
        glVertex3f(md.obj_points[md.obj_faces[i].vn[2]-1].x,md.obj_points[md.obj_faces[i].vn[2]-1].y,md.obj_points[md.obj_faces[i].vn[2]-1].z);
    }
    glEnd();
    glPopMatrix();
}

