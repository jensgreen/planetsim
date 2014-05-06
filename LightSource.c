#include "LightSource.h"

LightSource lightSources[NR_OF_LIGHTSOURCES];

void initLightSource(){
		Point3D color = {1.0f, 1.0f, 1.0f};
		Point3D position = {0.0f, 0.0f, 0.0f};

		lightSources[0].position= position;
		lightSources[0].intensity = 50;
		lightSources[0].color = color;

		Point3D color2 = {1.0f, 1.0f, 1.0f};
		Point3D position2 = {2.0f, 7.0f, 5.0f};

		lightSources[1].position= position2;
		lightSources[1].intensity = 50;
		lightSources[1].color = color2;
}


LightSource* getLightSource(){
	return lightSources;
}


