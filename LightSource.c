#include "LightSource.h"

LightSource lightSources[NR_OF_LIGHTSOURCES];

void initLightSource(){
		Point3D color = {0.8f, 0.0f, 0.0f};
		Point3D position = {5.0f, 5.0f, 0.0f};

		lightSources[0].position= position;
		lightSources[0].intensity = 100;
		lightSources[0].color = color;

		Point3D color2 = {0.0f, 0.2f, 0.0f};
		Point3D position2 = {2.0f, 7.0f, 5.0f};

		lightSources[1].position= position2;
		lightSources[1].intensity = 100;
		lightSources[1].color = color2;
}


LightSource* getLightSource(){
	return lightSources;
}


