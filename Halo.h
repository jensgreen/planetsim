#ifndef M_HALO
#define M_HALO
#include "VectorUtils3.h"
#include "loadobj.h"
typedef  struct{
	float terrainMaxRadius;
	vec3 velocity;
  vec3 position;
	mat4 scaleAndPos;
	Model *sphereModel;
} Halo;


void initHalo(Halo *halo, GLfloat x, GLfloat y, GLfloat z, char *modelPath);
void drawHalo(Halo *halo, mat4 tot, GLuint shader);
void scaleHalo(Halo *halo, float s);

// vec3 getSpherePosition(Sphere *sph);


#endif
