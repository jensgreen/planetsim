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
        printf("Size indexarray: %d, Size vertexArray: %d\n",sphereModel->numIndices, sphereModel->numVertices);
	vec3 curVer1, curVer2, curVer3, out;

//Empty normalArray
	for(int i=0; i<sphereModel->numVertices;i++){
		sphereModel->normalArray[i*3]=0.0;
		sphereModel->normalArray[i*3+1]=0.0;
		sphereModel->normalArray[i*3+1]=0.0;
	}


//Calculating normalVectors for every triangle and setting adding that normal to all three vertex normals
	for(int i=0; i<sphereModel->numIndices/3;i++){
      		curVer1.x = sphereModel->vertexArray[sphereModel->indexArray[i*3]*3+0];
        	curVer1.y = sphereModel->vertexArray[sphereModel->indexArray[i*3]*3+1];
        	curVer1.z = sphereModel->vertexArray[sphereModel->indexArray[i*3]*3+2];
        	curVer2.x = sphereModel->vertexArray[sphereModel->indexArray[i*3+1]*3+0];
        	curVer2.y = sphereModel->vertexArray[sphereModel->indexArray[i*3+1]*3+1];
        	curVer2.z = sphereModel->vertexArray[sphereModel->indexArray[i*3+1]*3+2];
        	curVer3.x = sphereModel->vertexArray[sphereModel->indexArray[i*3+2]*3+0];
        	curVer3.y = sphereModel->vertexArray[sphereModel->indexArray[i*3+2]*3+1];
        	curVer3.z = sphereModel->vertexArray[sphereModel->indexArray[i*3+2]*3+2];

		out = CalcNormalVector(curVer1, curVer2, curVer3);

		sphereModel->normalArray[sphereModel->indexArray[i*3]*3+0] += out.x;
		sphereModel->normalArray[sphereModel->indexArray[i*3]*3+1] += out.y;
		sphereModel->normalArray[sphereModel->indexArray[i*3]*3+2] += out.z;
		sphereModel->normalArray[sphereModel->indexArray[i*3+1]*3+0] += out.x;
		sphereModel->normalArray[sphereModel->indexArray[i*3+1]*3+1] += out.y;
		sphereModel->normalArray[sphereModel->indexArray[i*3+1]*3+2] += out.z;
		sphereModel->normalArray[sphereModel->indexArray[i*3+2]*3+0] += out.x;
		sphereModel->normalArray[sphereModel->indexArray[i*3+2]*3+1] += out.y;
		sphereModel->normalArray[sphereModel->indexArray[i*3+2]*3+2] += out.z;
	}	

	return sphereModel;
}


//Method assume that the model i a sphere and the sphere center is origo. Should be fixed before push.
Model* GenerateTerrain(Model *sphereModel, /*int scaleSphere,*/ int maxIterations, float addSubConst){
	vec3 newPos;
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
			
			newPos.x = sphereModel->vertexArray[3*i];//+sphereModel->normalArray[3*i];
			newPos.y = sphereModel->vertexArray[3*i+1];//+sphereModel->normalArray[3*i+1];
			newPos.z = sphereModel->vertexArray[3*i+2];//+sphereModel->normalArray[3*i+2];
			if(DotProduct(planeNorm, newPos)>0) {	
				newPos = VectorAdd(newPos, ScalarMult(pointNormal, addSubConst));
			} else {
				newPos = VectorSub(newPos, ScalarMult(pointNormal, addSubConst));
			}
			sphereModel->vertexArray[3*i] = newPos.x;
			sphereModel->vertexArray[3*i+1] = newPos.y;
			sphereModel->vertexArray[3*i+2] = newPos.z;
		}
	}

	sphereModel = ChangeNormals(sphereModel);

	return LoadDataToModel(sphereModel->vertexArray, sphereModel->normalArray, NULL, NULL, sphereModel->indexArray, sphereModel->numVertices, sphereModel->numIndices);
}

