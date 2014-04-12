#include "VectorUtils3.h"

typedef struct{
  vec3 position;
  GLfloat intensity;
  vec3 color;
} LightSource;



void initLightSource();
LightSource getLightSource();
