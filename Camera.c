#include "Camera.h"
Camera camera;

void initCamera(){

  camera.moveSpeed = 500;
  camera.mouseSens = 0.0005;

  camera.position.x = 0;
  camera.position.y = 0;
  camera.position.z = 0;

  camera.totalrot = IdentityMatrix();
/*int dy = 100;  
vec3 y = (vec3){0,1,0};
  y = MultVec3(camera.totalrot, y);
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

 vec3 dirvec = MultVec3(camera.totalrot,dir);
printf("x: %f, y: %f, z:%f\n",dirvec.x,dirvec.y,dirvec.z);
  camera.position = VectorAdd(camera.position, dirvec);
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
 mat4 frotMat; 
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

   
  


}

Camera getCamera(){
  return camera;
}

mat4 getViewMatrix(){
  return Mult(camera.totalrot,getCameraPositionMatrix());
}

mat4 getCameraPositionMatrix(){
  return T(camera.position.x, camera.position.y, camera.position.z);
}
