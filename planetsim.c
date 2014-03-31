// Lab 4, terrain generation

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
#include <math.h>

mat4 projectionMatrix;
float scaleXZ = 5.0, scaleY = 50.0;
int mapWidth;
/*
vec3 calculateNormal(vec3 v1, vec3 v2, vec3 v3){
	vec3 dir1 = v1-v2;
	vec3 dir2 = v1-v3;
	return CrossProduct(dir1, CrossProduct(dir1, dir2));
}
*/
/*Model* GenerateTerrain(TextureData *tex)
{
	mapWidth = tex->width;
	int vertexCount = tex->width * tex->height;
	int triangleCount = (tex->width-1) * (tex->height-1) * 2;
	int x, z;

	GLfloat *vertexArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *normalArray = malloc(sizeof(GLfloat) * 3 * vertexCount);
	GLfloat *texCoordArray = malloc(sizeof(GLfloat) * 2 * vertexCount);
	GLuint *indexArray = malloc(sizeof(GLuint) * triangleCount*3);

	printf("bpp %d\n", tex->bpp);
	for (x = 0; x < tex->width; x++)
		for (z = 0; z < tex->height; z++)
		{
			// Vertex array. You need to scale this properly
			vertexArray[(x + z * tex->width)*3 + 0] = x / scaleXZ;
			vertexArray[(x + z * tex->width)*3 + 1] = tex->imageData[(x + z * tex->width) * (tex->bpp/8)] / scaleY;
			vertexArray[(x + z * tex->width)*3 + 2] = z / scaleXZ;
			// Normal vectors. You need to calculate these.
			// 	
			vec3 p1;
			p1.x = vertexArray[(x + z * tex->width)*3 + 0];
			p1.y = vertexArray[(x + z * tex->width)*3 + 1];
			p1.z = vertexArray[(x + z * tex->width)*3 + 2];
			vec3 p2, p3;
			if(x-1 >= 0) {
				p2.x = vertexArray[(x-1 + z * tex->width)*3 + 0]; 
				p2.y = vertexArray[(x-1 + z * tex->width)*3 + 1];
				p2.z = vertexArray[(x-1 + z * tex->width)*3 + 2];
			} else { 
				p2.x = 1.0;
				p2.y = 0.0;
				p2.z = 0.0;
			}
			if(z-1 >= 0) {	
				p3.x = vertexArray[(x + (z-1) * tex->width)*3 + 0];
				p3.y = vertexArray[(x + (z-1) * tex->width)*3 + 1];
				p3.z = vertexArray[(x + (z-1) * tex->width)*3 + 2]; 
			} else { 
				p3.x = 1.0;
				p3.y = 0.0;
				p3.z = 1.0;
			}

			vec3 normalVector = CalcNormalVector(p1,p3,p2);
			normalArray[(x + z * tex->width)*3 + 0] = normalVector.x;
			normalArray[(x + z * tex->width)*3 + 1] = normalVector.y;
			normalArray[(x + z * tex->width)*3 + 2] = normalVector.z;
			// Texture coordinates. You may want to scale them.
			texCoordArray[(x + z * tex->width)*2 + 0] = x; // (float)x / tex->width;
			texCoordArray[(x + z * tex->width)*2 + 1] = z; // (float)z / tex->height;
		}
	for (x = 0; x < tex->width-1; x++)
		for (z = 0; z < tex->height-1; z++)
		{
			// Triangle 1
			indexArray[(x + z * (tex->width-1))*6 + 0] = x + z * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 1] = x + (z+1) * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 2] = x+1 + z * tex->width;
			// Triangle 2
			indexArray[(x + z * (tex->width-1))*6 + 3] = x+1 + z * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 4] = x + (z+1) * tex->width;
			indexArray[(x + z * (tex->width-1))*6 + 5] = x+1 + (z+1) * tex->width;
		}

	// End of terrain generation

	// Create Model and upload to GPU:

	Model* model = LoadDataToModel(
			vertexArray,
			normalArray,
			texCoordArray,
			NULL,
			indexArray,
			vertexCount,
			triangleCount*3);

	return model;
} */

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
float MOVE_SPEED = 3, MOUSE_SENS = 0.005;


// vertex array object
mat4 camMatrix;
int old_x, old_y;
// Reference to shader texprogram
GLuint texprogram, program;
GLuint tex1, tex2;
TextureData ttex; // terrain

Model* fuckUpModel(Model *sphereModel2){
	vec3 newPos;
	for(int i = 0; i < sphereModel2->numVertices; i++){
		newPos.x = sphereModel2->vertexArray[3*i]+sphereModel2->normalArray[3*i];
		newPos.y = sphereModel2->vertexArray[3*i+1]+sphereModel2->normalArray[3*i+1];
		newPos.z = sphereModel2->vertexArray[3*i+2]+sphereModel2->normalArray[3*i+2];
		newPos = ScalarMult(newPos, i*0.001);
		sphereModel2->vertexArray[3*i] = newPos.x;
		sphereModel2->vertexArray[3*i+1] = newPos.y;
		sphereModel2->vertexArray[3*i+2] = newPos.z;
	}

	return LoadDataToModel(sphereModel2->vertexArray, sphereModel2->normalArray, NULL, NULL, sphereModel2->indexArray, sphereModel2->numVertices, sphereModel2->numIndices);
}

void init(void)
{
	// GL inits
	glClearColor(0.2,0.2,0.5,0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	printError("GL inits");

	projectionMatrix = frustum(-0.1, 0.1, -0.1, 0.1, 0.2, 5000.0);

	// Load and compile shader
	texprogram = loadShaders("terrain.vert", "terrain.frag");
	program = loadShaders("diffuse.vert", "diffuse.frag");
	glUseProgram(texprogram);
	printError("init shader");

	glUniformMatrix4fv(glGetUniformLocation(texprogram, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
	glUniform1i(glGetUniformLocation(texprogram, "tex"), 0); // Texture unit 0

	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, GL_TRUE, projectionMatrix.m);
	// init camMatrix 
	vec3 cam = {0, 5, 8};
	vec3 lookAtPoint = {2, 0, 2};
	camMatrix = lookAt(cam.x, cam.y, cam.z,
			lookAtPoint.x, lookAtPoint.y, lookAtPoint.z,
			0.0, 1.0, 0.0);

	// Load models
	sphereModel = LoadModelPlus("HD_SPHERE_2015.obj");
	sphereModel = fuckUpModel(sphereModel);
	initSphere(&theSphere,10, 5, 0, 0.2);
	// Load terrain data
	printError("init terrain");
}


void processInput(){
	if (keyIsDown('d'))
		camMatrix = Mult(T(-MOVE_SPEED,0,0), camMatrix);
	if (keyIsDown('a'))
		camMatrix = Mult(T(MOVE_SPEED, 0, 0), camMatrix);
	if (keyIsDown('w'))
		camMatrix = Mult(T(0,0,MOVE_SPEED), camMatrix);

	if (keyIsDown('s'))
		camMatrix = Mult(T(0,0,-MOVE_SPEED), camMatrix);
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

	// Build matrix

	modelView = IdentityMatrix();
	total = Mult(camMatrix, modelView);
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

void mouse(int x, int y)
{

	camMatrix = Mult(Mult(Rx((float)(y-old_y)*MOUSE_SENS),Ry((float)(-(x-old_x))*MOUSE_SENS)), camMatrix); 
	old_x = x;
	old_y = y;
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitContextVersion(3, 2);
	glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow ("TSBK07 Lab 4");
	glutDisplayFunc(display);
	init ();
	initKeymapManager();
	glutTimerFunc(20, &timer, 0);

	glutPassiveMotionFunc(mouse);

	glutMainLoop();
	exit(0);
}
