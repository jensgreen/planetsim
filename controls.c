float MOVE_SPEED = 2, MOUSE_SENS = 0.002;
int old_x, old_y;


void mouse(int x, int y)
{
	rotateCamera(x-old_x, y-old_y);
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
}
