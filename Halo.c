#include "Halo.h"
#include "GenerateTerrain.h"
#include "VectorUtils3.h"
#include <stdlib.h>

void initHalo(Halo *halo, GLfloat x, GLfloat y, GLfloat z, char *modelPath){
	halo->scaleAndPos = Mult(T(x,y,z),IdentityMatrix());
	halo->position.x = x;
	halo->position.y = y;
	halo->position.z = z;
  halo->terrainMaxRadius = 1.0;
	halo->scale = 1.0;
  halo->model = LoadModelPlus(modelPath);
}

void scaleHalo(Halo *halo, float s) {
  halo->scaleAndPos = Mult(halo->scaleAndPos, S(s,s,s));
	halo->scale = s;
	halo->terrainMaxRadius*=s;
}

void drawHalo(Halo *halo, mat4 tot, GLuint shader) {
  glUseProgram(shader);
  mat4 total = tot;
  mat4 mdlview = halo->scaleAndPos;
  total = Mult(total, mdlview);
  glUniformMatrix4fv(glGetUniformLocation(shader, "mdlMatrix"), 1, GL_TRUE, total.m);
  DrawModel(halo->model, shader, "inPosition", "inNormal", NULL);	
}
