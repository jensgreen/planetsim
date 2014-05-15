#include "LightSource.h"

LightSource lightSource;

void initLightSource(){
		Point3D color = {0.8f, 0.0f, 0.8f};
		lightSource.intensity = 100;
		lightSource.color = color;
}


LightSource* getLightSource(){
	return &lightSource;
}

