
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
#include "Camera.h"



Halo haloes[1];


int WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;


// Reference to shaders
GLuint texprogram, program, haloProgram, lightsourceShader;
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
  lightsourceShader = loadShaders("lightsource.vert", "lightsource.frag");
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

  vec3 color;
  color = (vec3){0.6,0.2,0.2};
  // init planet 0
  initSphere(&planets[0],0, 0 ,2000,500, 0.7,"models/HD_SPHERE_2015.obj", color);
  scaleSphere(&planets[0],200);


  color = (vec3){0.55,0.8,1.0};
  //init planet 1
  initSphere(&planets[1],0, 0, -3000,500,0.4,"models/HD_SPHERE_2015.obj", color);
  scaleSphere(&planets[1],300);

  initSphere(&planets[2],10000, 0, -6000,800,0.2,"models/HD_SPHERE_2015.obj", color);
  scaleSphere(&planets[2],200);

  initSphere(&planets[3],1000, 0, -6000,1000,0.3,"models/HD_SPHERE_2015.obj", color);
  scaleSphere(&planets[3],500);
  // init the sun and the sphere for the sun
  initLightSource((vec3){0,0,0}, (vec3){1,0.75,0}, 100);
  initSphere(&getLightSource()->sphere, 0,0,0,300,0.1,"models/HD_SPHERE_2015.obj", color);
  scaleSphere(&getLightSource()->sphere, 400);
  initHalo(&haloes[0], 0, 0,0, "models/billboard.obj");
  scaleHalo(&haloes[0],700);
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

  drawSkybox(projectionMatrix, getCameraMat());
  drawHalo(&haloes[0], total, haloProgram);

  for(int i = 0; i < 4; i++){
    moveSphere(&planets[i]);
    drawSphere(&planets[i], total, program);
  }

  drawSphere(&getLightSource()->sphere, total, program);
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
