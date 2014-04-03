#include "Camera.h"
Camera camera;

void initCamera(){

  camera.moveSpeed = 0.7;
  camera.mouseSens = 0.005;
  
  camera.matrix = lookAt(10, 0, 10,
			0, 0, 0,
			0.0, 1.0, 0.0);
}

void moveCameraForward(){
		camera.matrix = Mult(T(0, 0, camera.moveSpeed), camera.matrix);
}

void moveCameraBack(){
		camera.matrix = Mult(T(0,0,-camera.moveSpeed), camera.matrix);
}

void moveCameraRight(){
		camera.matrix = Mult(T(-camera.moveSpeed,0,0), camera.matrix);
}

void moveCameraLeft(){
		camera.matrix = Mult(T(camera.moveSpeed, 0, 0), camera.matrix);
}

void rotateCamera(int dx, int dy){
	mat4 rotMat = Mult(Rx((float)(dy)*camera.mouseSens),Ry((float)(-(dx))*camera.mouseSens));
  camera.matrix = Mult(rotMat, camera.matrix);
}

Camera getCamera(){
  return camera;
}
