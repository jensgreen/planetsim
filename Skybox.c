#include "Skybox.h"

void initSkybox() {
  skyboxShader = loadShaders("skybox.vert", "skybox.frag");
  skyboxModel = LoadModelPlus("skybox.obj");
  LoadTGATextureSimple("SkyBox512.tga", &skyboxTex);
}

void drawSkybox(mat4 projMatrix, mat4 mdlMatrix) {
  GLuint shader = skyboxShader;
  glUseProgram(shader);
  glDisable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, skyboxTex);
  glUniform1i(glGetUniformLocation(skyboxShader, "texUnit"), 0); // texure unit 0
  
  // reset translation
  // mat4 skyboxMatrix = buildSkyboxMatrix(projMatrix, camMatrix);
  glUniformMatrix4fv(glGetUniformLocation(shader, "projMatrix"), 1, GL_TRUE, projMatrix.m);
  glUniformMatrix4fv(glGetUniformLocation(shader, "mdlMatrix"), 1, GL_TRUE, mdlMatrix.m);
  DrawModel(skyboxModel, shader, "inPosition", NULL, "inTexCoord");

  glEnable(GL_DEPTH_TEST);
}

mat4 buildSkyboxMatrix(mat4 projMatrix, mat4 camMatrix) {
  mat4 skyboxMatrix = Mult(projMatrix, camMatrix);
  skyboxMatrix.m[3] = 0;
  skyboxMatrix.m[7] = 0;
  skyboxMatrix.m[11] = 0;
  return skyboxMatrix;
}
