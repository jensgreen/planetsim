#include "VectorUtils3.h"

typedef struct{
  mat4 matrix;
  float moveSpeed;
  float mouseSens;
} Camera;

void initCamera();

Camera getCamera();

void moveCameraForward();
void moveCameraBack();
void moveCameraRight();
void moveCameraLeft();

void rotateCamera(int dx, int dy);
