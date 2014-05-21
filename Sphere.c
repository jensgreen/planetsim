#include "Sphere.h"
#include "GenerateTerrain.h"
#include <stdlib.h>

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
  glUniformMatrix4fv(glGetUniformLocation(p, "mdlMatrix"), 1, GL_TRUE, total.m);
  glUniform3fv(glGetUniformLocation(p, "direction"), 1, &sphere->position.x);
  DrawModel(sphere->sphereModel, p, "inPosition", "inNormal", NULL);	
}



vec3 getSpherePosition(Sphere *sph) {
  return (vec3){sph->scaleAndPos.m[3],sph->scaleAndPos.m[7],sph->scaleAndPos.m[11]};
}



void moveSphere(Sphere *sphere){
  
  vec3 pos = getSpherePosition(sphere);
  float distance = sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);

  sphere->scaleAndPos = Mult(Ry(10.0f/distance), sphere->scaleAndPos);
}

/*
// Hardcoded nr of planets to 2
Sphere getNearestSphere(){
  int nr_of_planets = 2;

  vec3 planetPos = planets[0].position;
  float dx = getCameraPosVec().x;
  float dy = getCameraPosVec().y;
  float dz = getCameraPosVec().z;

  double shortestDist = sqrt(dx*dx+dy*dy+dz*dz);
  double currentDistance;
  int indexToNearestSph = 0;

  for(int i = 1; i < nr_of_planets; i++){
    planetPos = planets[i].position;


    dx = getCameraPosVec().x;
    dy = getCameraPosVec().y;
    dz = getCameraPosVec().z;

    currentDistance = sqrt(dx*dx+dy*dy+dz*dz);

    if(currentDistance < shortestDist){
      indexToNearestSph = i;
      shortestDist = currentDistance;
    }

  }


  return planets[indexToNearestSph];
}
*/
