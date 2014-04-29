// VectorUtils3 header
// See source for more information

#ifndef __GENERATETERRAIN__
#define __GENERATETERRAIN__

#ifdef __APPLE__
	#include <OpenGL/gl3.h>
#else
	#include <GL/gl.h>
#endif
#include <math.h>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif


#include "loadobj.h"
	

typedef  struct{
	float terrainMaxRadius;
	vec3 velocity;
	mat4 scaleAndPos;
	Model *sphereModel
} Sphere;


//	void CopyVector(vec3 *v, vec3 *dest); // Will probably be removed
Model* GenerateTerrain(Sphere *sphereModel,/* int scaleSphere, */int maxIteration, float addSubConst);

void ChangeNormals(Sphere *sphere);
//Model* splitResizeModel(Model *sphereModel, GLfloat addConst, GLfloat subConst);
//Endif for ifndef __GENERATETERRAIN__
#endif
