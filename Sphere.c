#include "Sphere.h"

#include "GenerateTerrain.h"
void initSphere(Sphere *sphere,GLfloat x,GLfloat y, GLfloat z, int terIter, float terCons, char *s){
	sphere->scaleAndPos = Mult(T(x,y,z),IdentityMatrix());
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

void drawSphere(Sphere *sphere, mat4 tot,GLuint program){
  glUseProgram(program);
  mat4 total = tot;
  total = Mult(total, sphere->scaleAndPos);
  glUniformMatrix4fv(glGetUniformLocation(program, "mdlMatrix"), 1, GL_TRUE, total.m);
  DrawModel(sphere->sphereModel, program, "inPosition", "inNormal", NULL);	
}

vec3 getSpherePosition(Sphere *sph) {
  return (vec3){sph->scaleAndPos.m[3],sph->scaleAndPos.m[7],sph->scaleAndPos.m[11]};
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
