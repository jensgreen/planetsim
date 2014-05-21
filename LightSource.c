#include "LightSource.h"

LightSource lightSources;

void initLightSource(vec3 position, vec3 color, float intensity){
	lightSources.position = position;
	lightSources.color = color;
	lightSources.intensity = intensity;
}


LightSource* getLightSource(){
	return &lightSources;
}

Sphere* getLightSourceSphere(){
	return &lightSources.sphere;
}
