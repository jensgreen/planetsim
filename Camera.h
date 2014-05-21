#ifndef __CAMERA__
#define __CAMERA__

#include "VectorUtils3.h"
mat4 projectionMatrix;

typedef struct{
  vec3 position, forward, up;
  float moveSpeed;
  float mouseSens;
} Camera;

void initCamera();

mat4 getCameraMat();

void moveCamera(float x, float y, float z);
void moveCameraForward();
void moveCameraBack();
void moveCameraRight();
void moveCameraLeft();
void rotateCamera(int dx, int dy);


vec3 getCameraForwardVec();

vec3 getCameraUpVec();

vec3 getCameraPosVec();
#endif
