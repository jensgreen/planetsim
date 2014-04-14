#ifdef __APPLE__
	#include <OpenGL/gl3.h>
	#include "MicroGlut.h"
#endif
#include "GL_utilities.h"
#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "GenerateTerrain.h"
#include <math.h>
#include "controls.h"
#include "LightSource.h"

mat4 projectionMatrix;


typedef  struct{
	float radius;
	vec3 velocity;
	mat4 scaleAndPos;
} Sphere;

Sphere theSphere;
Model *sphereModel;

void initSphere(Sphere *sphere,float x,float z, float dx, float dz){
	sphere->scaleAndPos = IdentityMatrix();
	sphere->radius = 1.0;
	sphere->velocity.x = dx; 
	sphere->velocity.z = dz; 
}

void scaleSphere(Sphere *sphere, float s){
	sphere->scaleAndPos = Mult(sphere->scaleAndPos, S(s,s,s));
}



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
	sphereModel = LoadModel("VERY_HD_SPHERE_2015.obj");
	sphereModel = GenerateTerrain(sphereModel, 1000 , 0.7);
	initSphere(&theSphere,100, 100, 100, 0.2);
	scaleSphere(&theSphere,1000);
	// Load terrain data
	initLightSource();
	//init light
	printError("init terrain");
}


void uploadLightToShader(){
	getLightSource()[0].position.y -= 0.1;
	glUniform3fv(glGetUniformLocation(program, "lightSourcesPos"), NR_OF_LIGHTSOURCES, &getLightSource()[0].position.x);
	glUniform3fv(glGetUniformLocation(program, "lightSourcesColor"), NR_OF_LIGHTSOURCES, &getLightSource()[0].color.x);
}

void drawSphere(Sphere *sphere, mat4 tot){
	mat4 total = tot;
	total = Mult(total, sphere->scaleAndPos);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);
	DrawModel(sphereModel, program, "inPosition", "inNormal", NULL);	
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
	total = Mult(getCamera().matrix, modelView);
	glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);

	drawSphere(&theSphere, total);
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
	glutCreateWindow ("TSBK07 Lab 4");
	glutDisplayFunc(display);
	initCamera();
	initControls(WINDOW_WIDTH, WINDOW_HEIGHT);
	init ();
	initKeymapManager();
	glutTimerFunc(20, &timer, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}
