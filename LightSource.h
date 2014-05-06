#include "VectorUtils3.h"
#define NR_OF_LIGHTSOURCES 2

typedef struct{
  Point3D position;
  GLfloat intensity;
  Point3D color;
} LightSource;

void initLightSource();
LightSource* getLightSource();
