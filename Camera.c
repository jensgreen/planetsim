#include "Camera.h"
#include <math.h>
Camera camera;

void initCamera(){

  camera.moveSpeed = 500;
  camera.mouseSens = 0.0005;

  camera.position.x = 0;
  camera.position.y = 0;
  camera.position.z = 0;

//  camera.totalrot = IdentityMatrix();
camera.xRot = 0.0;
camera.yRot = 0.0;
/*int dy = 100;  
vec3 y = (vec3){0,1,0};
  y = MultVec3(camera.totalrot, y);
  otRot[0] = cy*cz;
  vec3 x = (vec3){1,0,0};
  x = MultVec3(camera.totalrot, x);
printf("xx: %f, xy: %f, xz:%f\n",x.x,x.y,x.z);
printf("yx: %f, yy: %f, yz:%f\n",y.x,y.y,y.z);

mat4 rotMat = ArbRotate(x, (float)(dy)*camera.mouseSens);
  camera.totalrot = Mult(camera.totalrot,rotMat);
*/}

void moveCamera(float x, float y, float z){
vec3 dir;
dir.x = x;
dir.y = y;
dir.z = z;
mat4 totRot = getCameraRotation();
printf("%f  %f  %f  %f\n",totRot.m[0],totRot.m[1],totRot.m[2],totRot.m[3]);
printf("%f  %f  %f  %f\n",totRot.m[4],totRot.m[5],totRot.m[6],totRot.m[7]);
printf("%f  %f  %f  %f\n",totRot.m[8],totRot.m[9],totRot.m[10],totRot.m[11]);
printf("%f  %f  %f  %f\n\n",totRot.m[12],totRot.m[13],totRot.m[14],totRot.m[15]);


vec3 dirvec = (vec3){-totRot.m[2]*z,totRot.m[6]*z,totRot.m[10]*z};


camera.position.x += dirvec.x;
camera.position.y += dirvec.y;
camera.position.z += dirvec.z;
		
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
camera.xRot += (float)(dy)*camera.mouseSens;
if(camera.xRot>M_PI){
	camera.xRot -= 2*M_PI;
} else if(camera.xRot <-M_PI){
	camera.xRot += 2*M_PI;
}
camera.yRot += (float)(dx)*camera.mouseSens;
if(camera.yRot>M_PI){
	camera.yRot -= 2*M_PI;
} else if(camera.yRot <-M_PI){
camera.yRot += 2*M_PI;
}
 /*mat4 frotMat; 
  if(dx != 0){
  vec3 y = (vec3){0,1,0};
  vec3 x = (vec3){1,0,0};

  frotMat = ArbRotate(y, (float)(dx)*camera.mouseSens);
  camera.totalrot = Mult(frotMat,camera.totalrot);
  }

  
  if(dy != 0 ){
vec3 x;
if(dx != 0){
	x = MultVec3(frotMat, (vec3){1,0,0});
} else {
  x = (vec3){1,0,0};
}  
vec3 y = (vec3){0,1,0};
mat4 rotMat = ArbRotate(x, (float)(dy)*camera.mouseSens);
	camera.totalrot = Mult(rotMat,camera.totalrot);
}  
*/


   
  


}

Camera getCamera(){
  return camera;
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

