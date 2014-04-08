#include "loadobj.h"
#include "VectorUtils3.h"
#include "GenerateTerrain.h"
#include <math.h>
#include <stdlib.h>

#ifdef __APPLE__                
        #include <OpenGL/gl3.h>  
#else                            
        #include <GL/gl.h>  
#endif 

Model* ChangeNormals(Model *sphereModel) {
	
	return sphereModel;
}


//Method assume that the model i a sphere and the sphere center is origo. Should be fixed before push.
Model* GenerateTerrain(Model *sphereModel, /*int scaleSphere,*/ int maxIterations, float addSubConst){
	vec3 newPos;
	
	//Scale up planet to a size we can handle
	/*
        for(int i = 0; i < sphereModel->numVertices; i++){
                newPos.x = sphereModel->vertexArray[3*i]+sphereModel->normalArray[3*i];
               	newPos.y = sphereModel->vertexArray[3*i+1]+sphereModel->normalArray[3*i+1];
                newPos.z = sphereModel->vertexArray[3*i+2]+sphereModel->normalArray[3*i+2];
                newPos = ScalarMult(newPos, scaleSphere);
               	sphereModel->vertexArray[3*i] = newPos.x;
               	sphereModel->vertexArray[3*i+1] = newPos.y;
               	sphereModel->vertexArray[3*i+2] = newPos.z;
        }
   */

	vec3 planeNorm;
	vec3 pointNormal;
	//Run resizeHalfAlgorithm
	for(int iterations = 0; iterations < maxIterations; iterations++){
		planeNorm.x = (double)rand() / (double)RAND_MAX - 0.5 ;
		planeNorm.y = (double)rand() / (double)RAND_MAX - 0.5 ;
		planeNorm.z = (double)rand() / (double)RAND_MAX - 0.5 ;
		planeNorm = Normalize(planeNorm);
        	for(int i = 0; i < sphereModel->numVertices; i++){
                	pointNormal.x = sphereModel->normalArray[3*i];
			pointNormal.y = sphereModel->normalArray[3*i+1];
			pointNormal.z = sphereModel->normalArray[3*i+2]; 
//			printf("%d,%d,%d : %f, %f, %f\n",sphereModel->indexArray[3*i],sphereModel->indexArray[3*i+1],sphereModel->indexArray[3*i+2], pointNormal.x, pointNormal.y, pointNormal.z);
			newPos.x = sphereModel->vertexArray[3*i];//+sphereModel->normalArray[3*i];
                	newPos.y = sphereModel->vertexArray[3*i+1];//+sphereModel->normalArray[3*i+1];
                	newPos.z = sphereModel->vertexArray[3*i+2];//+sphereModel->normalArray[3*i+2];
			if(DotProduct(planeNorm, newPos)>0) {	
                		newPos = VectorAdd(newPos, ScalarMult(pointNormal, addSubConst));
			} else {
                		newPos = VectorAdd(newPos, ScalarMult(ScalarMult(pointNormal, addSubConst),-1));
			}
                	sphereModel->vertexArray[3*i] = newPos.x;
                	sphereModel->vertexArray[3*i+1] = newPos.y;
                	sphereModel->vertexArray[3*i+2] = newPos.z;
        	}
	}
	
	sphereModel = ChangeNormals(sphereModel);

        return LoadDataToModel(sphereModel->vertexArray, sphereModel->normalArray, NULL, NULL, sphereModel->indexArray, sphereModel->numVertices, sphereModel->numIndices);
}

