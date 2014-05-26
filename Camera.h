#ifndef __CAMERA__
#define __CAMERA__

#include "VectorUtils3.h"
#include "Sphere.h"
mat4 projectionMatrix;

typedef struct{
	vec3 position, forward, up;
	float moveSpeed;
	float mouseSens;
	float radius;
} Camera;

void initCamera();

mat4 getCameraMat();

void moveCamera(float x, float y, float z);

void rotateCameraWithMat(mat4 camRot);

void moveCameraForward();
void moveCameraBack();
void moveCameraRight();
void moveCameraLeft();
float getCameraRadius();
void rotateCamera(int dx, int dy);
void translateCamera(vec3 velocity);

void setMoveSpeed(float speed);

vec3 getCameraForwardVec();

vec3 getCameraUpVec();

vec3 getCameraPosVec();
#endif
