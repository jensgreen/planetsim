#include "LightSource.h"

LightSource lightSources[NR_OF_LIGHTSOURCES];

void initLightSource(){
		Point3D color = {1.0f, 0.0f, 0.0f};
		Point3D position = {10.0f, 5.0f, 0.0f};

		lightSources[0].position= position;
		lightSources[0].intensity = 100;
		color.x = 1;
		color.y = 0;
		color.z = 0;
		lightSources[0].color = color;
}


LightSource* getLightSource(){
		return lightSources;
}


