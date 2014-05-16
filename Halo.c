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
  glDisable(GL_DEPTH_TEST); // draw halo behind all planets; should be drawn right behind current planet
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glUseProgram(shader);

  mat4 total = tot;
  mat4 mdlview = halo->scaleAndPos;
  total = Mult(total, mdlview);
  total = resetRotation(total, halo->scale);
  glUniformMatrix4fv(glGetUniformLocation(shader, "mdlMatrix"), 1, GL_TRUE, total.m);
  DrawModel(halo->model, shader, "inPosition", NULL, "inTexCoord");	

  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
}

mat4 resetRotation(mat4 tot, float scale) {
  //view-plane orient billboard (should be view-point orientation)
  //zero rotation, keep scale using scaled identity matrix. keep translation.
  mat4 total  = tot;
  total.m[0]  = scale; total.m[1] = 0.0;   total.m[2] = 0.0;
  total.m[4]  = 0.0;   total.m[5] = scale; total.m[6] = 0.0;
  total.m[8]  = 0.0;   total.m[9] = 0.0;   total.m[10] = scale;
  total.m[12] = 0.0;   total.m[13] = 0.0;  total.m[14] = 0.0; total.m[15] = 1;
  return total;
}

