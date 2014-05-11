#ifndef __CAMERA__
#define __CAMERA__

#include "VectorUtils3.h"

typedef struct{
float xRot, yRot;  
vec3 position;
  float moveSpeed;
  float mouseSens;
} Camera;

void initCamera();

Camera getCamera();
mat4 getCameraRotation();
void moveCamera(float x, float y, float z);
void moveCameraForward();
void moveCameraBack();
void moveCameraRight();
void moveCameraLeft();
void rotateCamera(int dx, int dy);
mat4 getViewMatrix();
mat4 getCameraPositionMatrix();

#endif
