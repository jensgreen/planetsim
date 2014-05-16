
#ifndef __PLANETSIM__
#define __PLANETSIM__

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
	// Linking hint for Lightweight IDE
	// uses framework Cocoa
#endif
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "GenerateTerrain.h"
#include <math.h>
#include "controls.h"
#include "Skybox.h"
#include "LightSource.h"
#include "Sphere.h"
#include "Halo.h"

mat4 projectionMatrix;


Sphere planets[2];
Halo haloes[1];


int WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;


// Reference to shaders
GLuint texprogram, program, haloProgram;
GLuint tex1, tex2;
TextureData ttex; // terrain


void init(void)
{
  // GL inits
  glClearColor(0,0,0,0);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  printError("GL inits");

  projectionMatrix = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 100000.0);

  // Load and compile shader
  texprogram = loadShaders("terrain.vert", "terrain.frag");
  program = loadShaders("untexturedlight.vert", "untexturedlight.frag");
  haloProgram = loadShaders("halo.vert", "halo.frag");
  glUseProgram(texprogram);
  printError("init shader");

  glUniformMatrix4fv(glGetUniformLocation(texprogram, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
  glUniform1i(glGetUniformLocation(texprogram, "tex"), 0); // Texture unit 0

  glUseProgram(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
  glUseProgram(haloProgram);
  glUniformMatrix4fv(glGetUniformLocation(haloProgram, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);

  glUseProgram(program);

  // Load models
  printf("Loading models\n");
  initSphere(&planets[0],0, 0 ,5000,0, 0,"HD_SPHERE_2015.obj");
  scaleSphere(&planets[0],1000);
  initHalo(&haloes[0], -10,-10,5000, "models/billboard.obj");
  scaleHalo(&haloes[0],2500);

  initSphere(&planets[1],0, 0, 10000,0,0,"HD_SPHERE_2015.obj");
  scaleSphere(&planets[1],1000);

  // Load terrain data
  initLightSource((vec3){0,0,-1000}, (vec3){1,0,0}, 100);
  //init light
  printError("init terrain");
}

float t;

void uploadLightToShader(){
  LightSource *ls = getLightSource();  
  glUniform3fv(glGetUniformLocation(program, "lightSourcesPos"), 1, &ls->position.x);
  glUniform3fv(glGetUniformLocation(program, "lightSourcesColor"), 1,&ls->color.x);
}


void display(void)
{
  processInput();

  // clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  mat4 total;

  printError("pre display");

  glUseProgram(program);
  uploadLightToShader();


  // Build matrix

  total = getCameraMat();
  glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);

  drawSkybox(projectionMatrix, getCameraMat());
  drawSphere(&planets[0], total, program);
  drawHalo(&haloes[0], total, haloProgram);
  drawSphere(&planets[1], total, program);
  printError("display 2");

  glutSwapBuffers();
}

void timer(int i)
{
  glutTimerFunc(20, &timer, i);
  glutPostRedisplay();
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
  glutInitContextVersion(3, 2);
  glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow ("PlanetSim");
  glutDisplayFunc(display);
  initSkybox();
  initCamera();
  initControls(WINDOW_WIDTH, WINDOW_HEIGHT);
  init ();
  initKeymapManager();
  glutTimerFunc(20, &timer, 0);

  glutPassiveMotionFunc(mouse);

  glutMainLoop();
  exit(0);
}
//Endif for ifndef __PLANETSIM__
#endif
