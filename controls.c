float MOVE_SPEED = 2, MOUSE_SENS = 0.002;
int old_x, old_y, width, height;

void initControls(int windowWidth, int windowHeight){
  width = windowWidth;
  height = windowHeight;
}

void mouse(int x, int y)
{
	rotateCamera(x-width/2, y-height/2);
  old_x = x;
	old_y = y;
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

  glutWarpPointer(width/2, height/2);
}
