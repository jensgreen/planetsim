#ifndef M_SPHERE
#define M_SPHERE
#include "VectorUtils3.h"
#include "loadobj.h"
typedef  struct{
	float terrainMaxRadius;
	vec3 velocity;
  vec3 position;
	mat4 scaleAndPos;
	Model *sphereModel;
} Sphere;

vec3 getSpherePosition(Sphere *sph);

void initSphere(Sphere *sphere,GLfloat x,GLfloat y, GLfloat z, int terIter, float terCons, char *s);
void drawSphere(Sphere *sphere, mat4 tot, GLuint p);

void scaleSphere(Sphere *sphere, float s);

//Sphere getNearestSphere();

#endif
