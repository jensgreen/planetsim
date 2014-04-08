#include "controls.h"
#ifdef __APPLE__
  #include <CoreGraphics/CoreGraphics.h>
  #include "glut.h"
#endif

float MOVE_SPEED = 2, MOUSE_SENS = 0.002;
int old_x, old_y, width, height;

void initControls(int windowWidth, int windowHeight){
  width = windowWidth;
  height = windowHeight;
}

void mouse(int x, int y)
{
  // Special mouse diff updating on OSX
  int diffx, diffy;
#ifdef __APPLE__
  CGGetLastMouseDelta(&diffx, &diffy);
#else
  diffx = x - (width / 2);
  diffy = y - (height / 2);
#endif

	rotateCamera(diffx, diffy);
}

void processInput(){
	if (keyIsDown('w'))
    moveCameraForward();   
	if (keyIsDown('s'))
    moveCameraBack();	  
  if (keyIsDown('d'))
	  moveCameraRight();
  if (keyIsDown('a'))
    moveCameraLeft();

// Update pointer pos in different ways on OSX and Linux
#ifdef __APPLE__
  CGPoint CenterPos = CGPointMake( width/2 + glutGet(GLUT_WINDOW_X), height/2 + glutGet(GLUT_WINDOW_Y));
  CGWarpMouseCursorPosition(CenterPos);
#else
  glutWarpPointer(width/2, height/2);
#endif

}
