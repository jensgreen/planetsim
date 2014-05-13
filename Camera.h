#ifndef __CAMERA__
#define __CAMERA__

#include "VectorUtils3.h"

typedef struct{
  float x,y,z,xRot,yRot;
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
mat4 getViewMatrix();
mat4 getCameraPositionMatrix();

mat4 getCameraTotRot();

vec3 getCameraForwardVec();

vec3 getCameraUpVec();

vec3 getCameraPosVec();
#endif
