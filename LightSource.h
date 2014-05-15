#include "VectorUtils3.h"
#include "GenerateTerrain.h"

typedef struct{
  GLfloat intensity;
  Point3D color;
  Sphere sphere;
} LightSource;

void initLightSource();
LightSource* getLightSource();
