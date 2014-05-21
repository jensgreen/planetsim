#include "VectorUtils3.h"
#include "Sphere.h"
#define NR_OF_LIGHTSOURCES 2

typedef struct{
  vec3 position;
  float intensity;
  vec3 color;
  Sphere sphere;
} LightSource;

void initLightSource(vec3 position, vec3 color, float intensity);
LightSource* getLightSource();

Sphere* getLightSourceSphere();
