
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

mat4 projectionMatrix;


Sphere planets[2];

void initSphere(Sphere *sphere,GLfloat x,GLfloat y, GLfloat z, int terIter, float terCons, char *s){
	sphere->scaleAndPos = Mult(T(x,y,z),IdentityMatrix());
	sphere->position.x = x;
	sphere->position.y = y;
	sphere->position.z = z;
	sphere->terrainMaxRadius = 1.0;
	sphere->sphereModel=LoadModelPlus(s);
	sphere->sphereModel = GenerateTerrain(sphere,terIter,terCons);
}

void scaleSphere(Sphere *sphere, float s){
	sphere->scaleAndPos = Mult(sphere->scaleAndPos, S(s,s,s));
	sphere->terrainMaxRadius*=s;
}

/*
// Hardcoded nr of planets to 2
Sphere getNearestSphere(){

  int nr_of_planets = 2;

  vec3 planetPos = planets[0].position;
  float dx = planetPos.x-getCamera().position.x;
  float dy = planetPos.y-getCamera().position.y;
  float dz = planetPos.z-getCamera().position.z;

  double shortestDist = sqrt(dx*dx+dy*dy+dz*dz);
  double currentDistance;
  int indexToNearestSph = 0;

  for(int i = 1; i < nr_of_planets; i++){
    planetPos = planets[i].position;


    dx = planetPos.x-getCamera().position.x;
    dy = planetPos.y-getCamera().position.y;
    dz = planetPos.z-getCamera().position.z;

    currentDistance = sqrt(dx*dx+dy*dy+dz*dz);

    if(currentDistance < shortestDist){
      indexToNearestSph = i;
      shortestDist = currentDistance;
    }

  }

  return planets[indexToNearestSph];
}
*/
int WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;


// Reference to shader texprogram
GLuint texprogram, program;
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
  glUseProgram(texprogram);
  printError("init shader");

  glUniformMatrix4fv(glGetUniformLocation(texprogram, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
  glUniform1i(glGetUniformLocation(texprogram, "tex"), 0); // Texture unit 0

  glUseProgram(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);



  // Load models
  printf("Loading models\n");
  initSphere(&planets[0],10000, 10000 ,10000,0, 0,"HD_SPHERE_2015.obj");

  scaleSphere(&planets[0],10000);


  initSphere(&planets[1],-10000, 0, -10000,0,0,"HD_SPHERE_2015.obj");
  scaleSphere(&planets[1],10000);

  // Load terrain data
  initLightSource();
  //init light
  //getNearestSphere();
  printError("init terrain");
}

float t;

void uploadLightToShader(){
  t += 0.03;
  getLightSource()[0].position.z = 10*cos(t);
  getLightSource()[0].position.y = 10*sin(t);


  getLightSource()[1].position.x = 10*cos(t);
  getLightSource()[1].position.y = 10*sin(t);

  vec3 colors[NR_OF_LIGHTSOURCES], positions[NR_OF_LIGHTSOURCES];

  for(int i = 0; i < NR_OF_LIGHTSOURCES; i++){
    colors[i] = getLightSource()[i].color;
    positions[i] = getLightSource()[i].position;
  }

  glUniform3fv(glGetUniformLocation(program, "lightSourcesPos"), NR_OF_LIGHTSOURCES, &positions[0].x);
  glUniform3fv(glGetUniformLocation(program, "lightSourcesColor"), NR_OF_LIGHTSOURCES, &colors[0].x);
}

void drawSphere(Sphere *sphere, mat4 tot){
  glUseProgram(program);
  mat4 total = tot;
  total = Mult(total, sphere->scaleAndPos);
  glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);
  DrawModel(sphere->sphereModel, program, "inPosition", "inNormal", NULL);	
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

  //getNearestSphere(); 

  // Build matrix

  total = getCameraMat();
  glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);

  drawSkybox(projectionMatrix, getCameraMat());
  drawSphere(&planets[0], total);
  drawSphere(&planets[1], total);
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
