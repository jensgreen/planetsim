#include "Skybox.h"

void initSkybox() {
  skyboxShader = loadShaders("skybox.vert", "skybox.frag");
  skyboxModel = LoadModelPlus("models/skybox.obj");
  LoadTGATextureSimple("starbox.tga", &skyboxTex);
}

void drawSkybox(mat4 projMatrix, mat4 camMatrix) {
  GLuint shader = skyboxShader;
  glUseProgram(shader);
  glDisable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, skyboxTex);
  glTexParameterf(GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_LINEAR);
  glUniform1i(glGetUniformLocation(skyboxShader, "texUnit"), 0); // texure unit 0
  
  mat4 skyboxMatrix = buildSkyboxMatrix(projMatrix, camMatrix);
  glUniformMatrix4fv(glGetUniformLocation(shader, "totalMatrix"), 1, GL_TRUE, skyboxMatrix.m);
  DrawModel(skyboxModel, shader, "inPosition", NULL, "inTexCoord");

  glEnable(GL_DEPTH_TEST);
}

mat4 buildSkyboxMatrix(mat4 projMatrix, mat4 camMatrix) {
  mat4 tmp = camMatrix;
  // reset translation
  tmp.m[3] = 0;
  tmp.m[7] = 0;
  tmp.m[11] = 0;
  return Mult(projMatrix, tmp);
}
