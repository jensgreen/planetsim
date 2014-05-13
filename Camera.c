#include "Camera.h"
#include <math.h>
Camera camera;

void initCamera(){

<<<<<<< HEAD
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
<<<<<<< HEAD
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

mat4 getCameraRotation(){
mat4 totRot = ArbRotate((vec3){1,0,0}, camera.xRot);
totRot = Mult(totRot,ArbRotate((vec3){0,1,0}, camera.yRot));
return totRot;
}

mat4 getViewMatrix(){
mat4 totRot = getCameraRotation();

/*
    float sx, sy, sz, cx, cy, cz, theta;
	vec3 left,up,forward;
    // rotation angle about X-axis (pitch)
    theta = camera.xRot;
    sx = sinf(theta);
    cx = cosf(theta);

    // rotation angle about Y-axis (yaw)
    theta = camera.yRot;
    sy = sinf(theta);
    cy = cosf(theta);

    // rotation angle about Z-axis (roll)
    theta = 0.0;;
    sz = sinf(theta);
    cz = cosf(theta);

mat4 totRot;
totRot.m[0] = cy*cz;
totRot.m[1] = -cy*sz;
totRot.m[2] = sy;
totRot.m[3] = 0.0;
totRot.m[4] = sx*sy*cz+cx*sz;
totRot.m[5] = -sx*sy*sz+cx*cz;
totRot.m[6] = -sx*cy;
totRot.m[7] = 0.0;
totRot.m[8] = -cx*sy*cz+sx*sz;
totRot.m[9] = cx*sy*sz+sx*cz;
totRot.m[10] = cx*cy;
totRot.m[11] = 0.0;
totRot.m[12] = 0.0;
totRot.m[13] = 0.0;
totRot.m[14] = 0.0;
totRot.m[15] = 1.0;

    // determine left axis
    left.x = cy*cz;
    left.y = sx*sy*cz + cx*sz;
    left.z = -cx*sy*cz + sx*sz;

    // determine up axis
    up.x = -cy*sz;
    up.y = -sx*sy*sz + cx*cz;
    up.z = cx*sy*sz + sx*cz;

    // determine forward axis
    forward.x = sy;
    forward.y = -sx*cy;
    forward.z = cx*cy;
*/
/*

float Q1a =  cos(camera.xRot/2) ;
vec3 Q1v = (vec3){sin(camera.xRot/2), 0, 0};
float Q2a =  cos(camera.yRot/2) ;
vec3 Q1v = (vec3){ 0,sin(camera.yRot/2), 0};
float Q2a =  cos(0) ;
vec3 Q1v = (vec3){ 0,0,0};

*/
/*

    Rx           Ry          Rz
// |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
	    / 0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
/ |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
vec3 x = (vec3){1.0,0.0,0.0};
mat4 totRot = ArbRotate(x,camera.xRot);
vec3 lookingVector = (vec3){1.0*sin(fmod(camera.xRot,2*M_PI)),cos(fmod(camera.xRot,2*M_PI)),1.0*cos(fmod(camera.xRot,2*M_PI))};
vec3 yRotVec = CrossProduct(lookingVector,x);
printf("x: %f, y: %f, z: %f ||",lookingVector.x, lookingVector.y, lookingVector.z);
printf("x: %f, y: %f, z: %f\n",yRotVec.x, yRotVec.y, yRotVec.z);
totRot = Mult(ArbRotate(yRotVec,camera.yRot),totRot);
*/  return Mult(totRot,getCameraPositionMatrix());
}

mat4 getCameraPositionMatrix(){
  return T(camera.position.x, camera.position.y, camera.position.z);
}

