#include "LightSource.h"

LightSource theSource;

void initLightSource(){
  vec3 color, position;

  position.x = 10;
  position.y = 0;
  position.z = 10;
  theSource.position = position;
  theSource.intensity = 100;
  color.x = 1;
  color.y = 0;
  color.z = 0;
  theSource.color = color;
}


LightSource getLightSource(){
  return theSource;
}
