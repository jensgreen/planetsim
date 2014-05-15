#include "Halo.h"
#include "GenerateTerrain.h"
#include <stdlib.h>

void initHalo(Halo *halo, GLfloat x, GLfloat y, GLfloat z, char *modelPath){
	halo->scaleAndPos = Mult(T(x,y,z),IdentityMatrix());
	halo->position.x = x;
	halo->position.y = y;
	halo->position.z = z;
	halo->terrainMaxRadius = 1.0;
  halo->sphereModel = LoadModelPlus(modelPath);
}

void scaleHalo(Halo *halo, float s) {
	halo->scaleAndPos = Mult(halo->scaleAndPos, S(s,s,s));
	halo->terrainMaxRadius*=s;
}

void drawHalo(Halo *halo, mat4 tot, GLuint shader) {
  glUseProgram(shader);
  mat4 total = tot;
  total = Mult(total, halo->scaleAndPos);
  glUniformMatrix4fv(glGetUniformLocation(shader, "mdlMatrix"), 1, GL_TRUE, total.m);
  DrawModel(halo->sphereModel, shader, "inPosition", "inNormal", NULL);	
}

// vec3 getHaloPosition(Halo *halo) {
//   return (vec3){halo->scaleAndPos.m[3],halo->scaleAndPos.m[7],halo->scaleAndPos.m[11]};
// }
