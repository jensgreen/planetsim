#ifndef M_SPHERE
#define M_SPHERE
#include "VectorUtils3.h"
#include "loadobj.h"
#include <stdbool.h> 
typedef  struct{
	float terrainMaxRadius;
	vec3 velocity;
  vec3 position;
	mat4 scaleAndPos;
  float rot;
	Model *sphereModel;
} Sphere;

vec3 getSpherePosition(Sphere *sph);

void initSphere(Sphere *sphere,GLfloat x,GLfloat y, GLfloat z, int terIter, float terCons, char *s);
void drawSphere(Sphere *sphere, mat4 tot, GLuint p);

void scaleSphere(Sphere *sphere, float s);

void moveSphere(Sphere *sphere);

bool inFrustum(mat4 spherePos, Sphere *sphere);
//Sphere getNearestSphere();

#endif
