
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

Sphere planets[1];

void initSphere(Sphere *sphere,GLfloat x,GLfloat y, GLfloat z, int terIter, float terCons, char *s){
	sphere->scaleAndPos = Mult(T(x,y,z),IdentityMatrix());
	
	sphere->terrainMaxRadius = 1.0;
	sphere->sphereModel=LoadModelPlus(s);
	sphere->sphereModel = GenerateTerrain(sphere,terIter,terCons);
	printf("Sphere maxradius: %f\n", sphere->terrainMaxRadius);
}

void scaleSphere(Sphere *sphere, float s){
	sphere->scaleAndPos = Mult(sphere->scaleAndPos, S(s,s,s));
	sphere->terrainMaxRadius*=s;
}



int WINDOW_HEIGHT = 1000, WINDOW_WIDTH = 1000;


// Reference to shader texprogram
GLuint texprogram, program;
GLuint tex1, tex2;
TextureData ttex; // terrain
float left = -0.1, right = 0.1, down = -0.1, up = 0.1, znear = 0.2, zfar = 100000.0;

void init(void)
{
	// GL inits
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	printError("GL inits");

	projectionMatrix = frustum(left, right, down, up, znear, zfar);

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
	initSphere(&planets[0],10, 10 ,10,0, 0.1,"HD_SPHERE_2015.obj");

	scaleSphere(&planets[0],10000);



	// Load terrain data
	initLightSource();
	//init light
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

bool isInFrustum(mat4 tot)
{
	mat4 projSphere = Mult(projectionMatrix, tot);
	printf("x: %f, y: %f, z: %f\n",getCamera().matrix.m[3],getCamera().matrix.m[7],getCamera().matrix.m[11]);
	
	vec3 left = (vec3){projectionMatrix.m[3]+projectionMatrix.m[0],projectionMatrix.m[7]+projectionMatrix.m[4],projectionMatrix.m[11]+projectionMatrix.m[8]};
	vec3 right = (vec3){projectionMatrix.m[3]-projectionMatrix.m[0],projectionMatrix.m[7]-projectionMatrix.m[4],projectionMatrix.m[11]-projectionMatrix.m[8]};
	vec3 bot = (vec3){projectionMatrix.m[3]+projectionMatrix.m[1],projectionMatrix.m[7]+projectionMatrix.m[5],projectionMatrix.m[11]+projectionMatrix.m[9]};
	vec3 top = (vec3){projectionMatrix.m[3]-projectionMatrix.m[1],projectionMatrix.m[7]-projectionMatrix.m[5],projectionMatrix.m[11]-projectionMatrix.m[9]};	
	vec3 far = (vec3){projectionMatrix.m[3]-projectionMatrix.m[2],projectionMatrix.m[7]-projectionMatrix.m[6],projectionMatrix.m[11]-projectionMatrix.m[10]};	
	vec3 near = (vec3){projectionMatrix.m[3]+projectionMatrix.m[2],projectionMatrix.m[7]+projectionMatrix.m[6],projectionMatrix.m[11]+projectionMatrix.m[10]};
	
//	float dp = DotProduct((vec4){projSphere.m[0], projSphere.m[5], projSphere.m[10],projSphere.m[15]},(vec4){projectionMatrix.m[0],projectionMatrix.m[1],projectionMatrix.m[2],projectionMatrix.m[3]});	

	float dp = projSphere.m[0]*(projectionMatrix.m[0]+projectionMatrix.m[12])+ projSphere.m[5]*(projectionMatrix.m[1]+projectionMatrix.m[13])+projSphere.m[10]*(projectionMatrix.m[2]+projectionMatrix.m[14])+projSphere.m[15]*(projectionMatrix.m[3]+projectionMatrix.m[15]); 

	//printf("x: %f, y: %f, z: %f\n", left.x,left.y, left.z);
	//printf("x: %f, y: %f, z: %f\n\n", projSphere.m[0], projSphere.m[5], projSphere.m[10]); 	
	printf("dotLeft: %f\n", dp);
	return true;
}

void drawSphere(Sphere *sphere, mat4 tot, mat4 c){
	glUseProgram(program);
	mat4 total = tot;
	sphere->scaleAndPos=Mult(sphere->scaleAndPos,Ry(0.01));
	//total = Mult(total, sphere->scaleAndPos);
	//total = Mult(total, c);
	isInFrustum(sphere->scaleAndPos);
	total = Mult(c, sphere->scaleAndPos);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);
	DrawModel(sphere->sphereModel, program, "inPosition", "inNormal", NULL);	
}


void display(void)
{
	processInput();

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 total, modelView;

	printError("pre display");

	glUseProgram(program);
	uploadLightToShader();

	// Build matrix

	modelView = IdentityMatrix();
	//total = Mult(getCamera().matrix, modelView);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);

	drawSkybox(projectionMatrix, getCamera().matrix);
	drawSphere(&planets[0], modelView, getCamera().matrix);
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
