#include "Camera.h"
Camera camera;

void initCamera(){

  camera.moveSpeed = 100;
  camera.mouseSens = 0.0005;
	camera.x = 0;
	camera.y = 0;
	camera.z = 0;
	camera.xRot = 0;
	camera.yRot = 0;
}

void moveCamera(float x, float y, float z){
	vec3 forward = getCameraForwardVec();
	camera.x += forward.x*z;
	camera.y += forward.y*z;
	camera.z += forward.z*z;
}

void moveCameraForward(){
  moveCamera(0,0,camera.moveSpeed);
}

void moveCameraBack(){
  moveCamera(0,0,-camera.moveSpeed);
}

void moveCameraRight(){
  moveCamera(-camera.moveSpeed, 0,0);
}

void moveCameraLeft(){
  moveCamera(camera.moveSpeed, 0,0);
}

void rotateCamera(int dx, int dy){
	camera.xRot += dy*camera.mouseSens;
	camera.yRot += dx*camera.mouseSens;
}

vec3 getCameraForwardVec(){
	mat4 totRot = getCameraTotRot();
	vec3 forward = (vec3){totRot.m[2],totRot.m[6],totRot.m[10]};
	return forward; 
}

vec3 getCameraUpVec(){
	mat4 totRot = getCameraTotRot();
	vec3 up = (vec3){totRot.m[1],totRot.m[5],totRot.m[9]};
	return up;
}

mat4 getCameraTotRot(){
	return Mult(ArbRotate((vec3){1,0,0},camera.xRot),ArbRotate((vec3){0,1,0},camera.yRot));
}

vec3 getCameraPosVec(){
	return (vec3){camera.x,camera.y,camera.z};
}

mat4 getCameraMat(){
  return Mult(getCameraTotRot(),T(camera.x,camera.y,camera.z));
}
