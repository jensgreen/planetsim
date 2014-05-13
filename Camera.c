#include "Camera.h"
#include <math.h>
Camera camera;

void initCamera(){

  camera.moveSpeed = 100;
  camera.mouseSens = 0.0005;
	camera.position.x = 0;
	camera.position.y = 0;
	camera.position.z = 0;
	camera.up.x = 0;
	camera.up.y = 1;
	camera.up.z = 0;
	camera.forward.x = 0;
	camera.forward.y = 0;
	camera.forward.z = 1;
}

void moveCamera(float x, float y, float z){
	camera.position.x += camera.forward.x*z;
	camera.position.y += camera.forward.y*z;
	camera.position.z += camera.forward.z*z;
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
	camera.forward = MultVec3(ArbRotate(camera.up, -dx*camera.mouseSens),camera.forward);
	vec3 side = CrossProduct(camera.forward, camera.up);
	mat4 sideRot = ArbRotate(side, -dy*camera.mouseSens);
	camera.forward = MultVec3(sideRot, camera.forward);
	camera.up = CrossProduct(side,camera.forward);
//camera.xRot += dy*camera.mouseSens;
	//camera.yRot += dx*camera.mouseSens;
}

vec3 getCameraForwardVec(){
	return camera.forward;
}

vec3 getCameraUpVec(){
	return camera.up;
}

vec3 getCameraPosVec(){
	return camera.position;
}

mat4 getCameraMat(){
  return lookAtv(camera.position, VectorAdd(camera.position,camera.forward),camera.up);
}


