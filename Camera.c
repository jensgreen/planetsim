#include "Camera.h"
Camera camera;

void initCamera(){

  camera.moveSpeed = 50;
  camera.mouseSens = 0.05;

  camera.position.x = 0;
  camera.position.y = 0;
  camera.position.z = 0;

  camera.totalrot = IdentityMatrix();
}

void moveCamera(float x, float y, float z){
  vec3 dir;
  dir.x = x;
  dir.y = y;
  dir.z = z;
  vec3 dirvec = MultVec3(camera.totalrot, dir);
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
  vec3 x = (vec3){1,0,0};
  vec3 y = (vec3){0,1,0};
  x = MultVec3(camera.totalrot, x);
  y = MultVec3(camera.totalrot, y);
  
  vec3 scalX, scalY;
  
  if(dx > 0 ){
    scalX= ScalarMult(x, dx);
  }else{
    scalX = (vec3){0,0,0};
  }

  if(dy > 0){
    scalY = ScalarMult(y, dy);
  }else{
    scalY = (vec3){0,0,0};
  }

  //mat4 rotMat = ArbRotate(x, (float)(dy)*camera.mouseSens);
  mat4 rotMat = ArbRotate(Normalize(VectorAdd(scalX,scalY)), camera.mouseSens);
  //mat4 rotMat = Mult(Rx((float)(dy)*camera.mouseSens),Ry((float)(-(dx))*camera.mouseSens));
  camera.totalrot = Mult(camera.totalrot, rotMat);
}

Camera getCamera(){
  return camera;
}

mat4 getViewMatrix(){
  return Mult(camera.totalrot, getCameraPositionMatrix());
}

mat4 getCameraPositionMatrix(){
  return T(camera.position.x, camera.position.y, camera.position.z);
}
