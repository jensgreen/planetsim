#ifndef M_HALO
#define M_HALO
#include "VectorUtils3.h"
#include "loadobj.h"
typedef  struct{
  float terrainMaxRadius;
	float scale;
	vec3 velocity;
  vec3 position;
	mat4 scaleAndPos;
	Model *model;
} Halo;

void initHalo(Halo *halo, GLfloat x, GLfloat y, GLfloat z, char *modelPath);
void drawHalo(Halo *halo, mat4 tot, GLuint shader);
void scaleHalo(Halo *halo, float s);
mat4 resetRotation(mat4 tot, float scale);

#endif
