#include "VectorUtils3.h"
#include "loadobj.h"
#include "LoadTGA.h"
#include "GL_utilities.h"

GLuint skyboxShader;
GLuint skyboxTex;
Model *skyboxModel;

void initSkybox();
void drawSkybox();
// Builds model-to-view skybox matrix
mat4 buildSkyboxMatrix(mat4 projMatrix, mat4 camMatrix);