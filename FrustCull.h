// VectorUtils3 header
// See source for more information

#ifndef __FRUSTCULL__
#define __FRUSTCULL__

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
	


void Method1(Model *sphereModel);

//Model* splitResizeModel(Model *sphereModel, GLfloat addConst, GLfloat subConst);
//Endif for ifndef __GENERATETERRAIN__
#endif
