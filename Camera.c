#include "Camera.h"
#include <math.h>
Camera camera;

void initCamera(){

	camera.moveSpeed = 100;
	camera.mouseSens = 0.0005;
	camera.radius = 50;
	camera.position.x = 4000;
	camera.position.y = 400;
	camera.position.z = 0;
	camera.up.x = 0;
	camera.up.y = 1;
	camera.up.z = 0;
	camera.forward.x = 0;
	camera.forward.y = 0;
	camera.forward.z = 1;
}

// moves the camera when using keyboard input
void moveCamera(float x, float y, float z){

	vec3 from = (vec3){camera.position.x + camera.forward.x*z,camera.position.y + camera.forward.y*z,camera.position.z + camera.forward.z*z};

	if(getDistanceToNearestSphere(planets, from) > 0){

		camera.position.x += camera.forward.x*z;
		camera.position.y += camera.forward.y*z;
		camera.position.z += camera.forward.z*z;
	}
}

void rotateCameraWithMat(mat4 camRot) {
	camera.position = MultVec3(camRot,camera.position);
	camera.forward = MultVec3(camRot, camera.forward);
	camera.up = MultVec3(camRot, camera.up);	
}

// moves the camera to a position in space
void translateCamera(vec3 velocity){
	camera.position = VectorAdd(camera.position, velocity);
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

void setMoveSpeed(float speed){
  camera.moveSpeed = speed;
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

float getCameraRadius(){
	return camera.radius;
}

