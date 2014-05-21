#include "Sphere.h"
#include "GenerateTerrain.h"
#include <stdlib.h>
#include "Camera.h"



void initSphere(Sphere *sphere,GLfloat x,GLfloat y, GLfloat z, int terIter, float terCons, char *s){
	sphere->scaleAndPos = Mult(T(x,y,z),IdentityMatrix());
	sphere->rot = 0;
	sphere->position.x = x;
	sphere->position.y = y;
	sphere->position.z = z;
	sphere->terrainMaxRadius = 1.0;
	sphere->sphereModel=LoadModelPlus(s);
	sphere->sphereModel = GenerateTerrain(sphere,terIter,terCons);
}

void scaleSphere(Sphere *sphere, float s){
	sphere->scaleAndPos = Mult(sphere->scaleAndPos, S(s,s,s));
	sphere->terrainMaxRadius*=s;
}

void drawSphere(Sphere *sphere, mat4 tot,GLuint p){
	glUseProgram(p);
	mat4 total = tot;
	total = Mult(total, sphere->scaleAndPos);
	if(inFrustum(total, sphere)){
		glUniformMatrix4fv(glGetUniformLocation(p, "mdlMatrix"), 1, GL_TRUE, total.m);
		glUniform3fv(glGetUniformLocation(p, "direction"), 1, &sphere->position.x);
		DrawModel(sphere->sphereModel, p, "inPosition", "inNormal", NULL);	
	}
}

bool inFrustum(mat4 spherePos, Sphere *sphere)
{

	mat4 matrix = projectionMatrix;

	float haxRLConstant = 0.6f;

	vec3 left = (vec3){matrix.m[3]+matrix.m[0],matrix.m[7]+matrix.m[4],matrix.m[11]+matrix.m[8]-haxRLConstant};
	vec3 r = (vec3){matrix.m[3]-matrix.m[0],matrix.m[7]-matrix.m[4],matrix.m[11]-matrix.m[8]-haxRLConstant};
	vec3 bot = (vec3){matrix.m[3]+matrix.m[1],matrix.m[7]+matrix.m[5],matrix.m[11]+matrix.m[9]-haxRLConstant};
	vec3 top = (vec3){matrix.m[3]-matrix.m[1],matrix.m[7]-matrix.m[5],matrix.m[11]-matrix.m[9]-haxRLConstant};        
	vec3 far = (vec3){matrix.m[3]-matrix.m[2],matrix.m[7]-matrix.m[6],matrix.m[11]-matrix.m[10]};       
	vec3 near = (vec3){matrix.m[3]+matrix.m[2],matrix.m[7]+matrix.m[6],matrix.m[11]+matrix.m[10]};
	/*	
		printf("left.x %f,left.y %f,left.z %f\n", left.x, left.y, left.z);
		printf("right.x %f,right.y %f,right.z %f\n", r.x, r.y, r.z);	
		printf("bot.x %f,bot.y %f,bot.z %f\n", bot.x, bot.y, bot.z);
		printf("top.x %f,top.y %f,top.z %f\n", top.x, top.y, top.z);
		printf("far.x %f,far.y %f,far.z %f\n", far.x, far.y, far.z);
		printf("near.x %f,near.y %f,near.z %f\n", near.x, near.y, near.z);
		printf("sp.x %f,sp.y %f,sp.z %f\n", spherePos.m[3], spherePos.m[7], spherePos.m[11]);
	 */	
	vec3 pos;

	pos = VectorAdd((vec3){spherePos.m[3], spherePos.m[7], spherePos.m[11]},ScalarMult(Normalize(r),sphere->terrainMaxRadius));	
	float dr = DotProduct(pos,r);

	pos = VectorAdd((vec3){spherePos.m[3], spherePos.m[7], spherePos.m[11]},ScalarMult(Normalize(left),sphere->terrainMaxRadius));		
	float dl = DotProduct(pos,left);

	pos = VectorAdd((vec3){spherePos.m[3], spherePos.m[7], spherePos.m[11]},ScalarMult(Normalize(top),sphere->terrainMaxRadius));	
	float dt = DotProduct(pos,top);

	pos = VectorAdd((vec3){spherePos.m[3], spherePos.m[7], spherePos.m[11]},ScalarMult(Normalize(bot),sphere->terrainMaxRadius));	
	float db = DotProduct(pos,bot);

	/*
	   printf("dotenr: %f\n", dr);
	   printf("dotenl: %f\n", dl);
	   printf("dotenu: %f\n", dt);
	   printf("dotend: %f\n\n", db);
	 */
	return (dr>=0&&dl>=0&&dt>=0&&db>=0);





}


vec3 getSpherePosition(Sphere *sph) {
	return (vec3){sph->scaleAndPos.m[3],sph->scaleAndPos.m[7],sph->scaleAndPos.m[11]};
}



void moveSphere(Sphere *sphere){

	vec3 pos = getSpherePosition(sphere);
	float distance = sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
	mat4 rotMat = Ry(10.0f/distance);
	mat4 newPosMat = Mult(rotMat, sphere->scaleAndPos);

	if(getDistanceToSphere(sphere, getCameraPosVec()) < 1000){	
		rotateCameraWithMat(rotMat);
	}
	
	sphere->scaleAndPos = newPosMat;
}

// Hardcoded nr of planets to 2
double getDistanceToNearestSphere(Sphere *planets, vec3 from){
	int nr_of_planets = 2;

	double shortestDist = getDistanceToSphere(getLightSourceSphere(), from); 
	double currentDistance;
	int indexToNearestSph = 0;

	for(int i = 0; i < nr_of_planets; i++){
		currentDistance = getDistanceToSphere(&planets[i], from);	
		printf("currentDistance = %lf for sphere %i\n", currentDistance, i);
		if(currentDistance < shortestDist){
			indexToNearestSph = i;
			shortestDist = currentDistance;
		}
	}
	printf("shortest dist = %lf\n\n", shortestDist);

	return shortestDist;
}

double getDistanceToSphere(Sphere *sphere, vec3 from){
	vec3 planetPos = getSpherePosition(sphere);

	float dx = from.x-planetPos.x;
	float dy = from.y-planetPos.y;
	float dz = from.z-planetPos.z;

	return sqrt(dx*dx+dy*dy+dz*dz) - getCameraRadius() - sphere->terrainMaxRadius;

}
