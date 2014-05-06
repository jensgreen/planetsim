#include "Camera.h"
Camera camera;

void initCamera(){

  camera.moveSpeed = 50;
  camera.mouseSens = 0.0005;

  camera.position.x = 0;
  camera.position.y = 0;
  camera.position.z = 0;

  camera.matrix = lookAt(camera.position.x, camera.position.y, camera.position.z,
      1, 0, 0,
      0.0, 1.0, 0.0);
  camera.totalrot = IdentityMatrix();
}

void moveCamera(float x, float y, float z){
  vec3 dir;
  dir.x = x;
  dir.y = y;
  dir.z = z;
  vec3 dirvec = MultVec3(camera.totalrot, dir);

  camera.position = VectorAdd(camera.position, dirvec);
  printf("@Camera.h: camera.position: %f, %f, %f\n", camera.position.x, camera.position.y, camera.position.z);
  camera.matrix = Mult(T(dir.x, dir.y, dir.z), camera.matrix);
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
  mat4 rotMat = Mult(Rx((float)(dy)*camera.mouseSens),Ry((float)(-(dx))*camera.mouseSens));
  camera.totalrot = Mult(camera.totalrot, rotMat);
  camera.matrix = Mult(rotMat, camera.matrix);

}

Camera getCamera(){
  return camera;
}
