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
	GLfloat normals[sphereModel->numVertices*3];	
	for(int i=0; i<sphereModel->numIndices/3;i++){
        printf("%d\n",i);
        /*printf("%d:%f, %f, %f\n",sphereModel->indexArray[i*3], sphereModel->vertexArray[sphereModel->indexArray[i*3]+0], sphereModel->vertexArray[sphereModel->indexArray[i*3]+1], sphereModel->vertexArray[sphereModel->indexArray[i*3]+0]);
 *        
 *                        printf("%d:%f, %f, %f\n",sphereModel->indexArray[i*3+1], sphereModel->vertexArray[sphereModel->indexArray[i*3+1]+0], sphereModel->vertexArray[sphereModel->indexArray[i*3+1]+1], sphereModel->vertexArray[sphereModel->indexArray[i*3+1]+0]);
 *                                        printf("%d:%f, %f, %f\n",sphereModel->indexArray[i*3+2], sphereModel->vertexArray[sphereModel->indexArray[i*3+2]+0], sphereModel->vertexArray[sphereModel->indexArray[i*3+2]+1], sphereModel->vertexArray[sphereModel->indexArray[i*3+2]+0]);
*/      curVer1.x = sphereModel->vertexArray[sphereModel->indexArray[i*3]*3+0];
        curVer1.y = sphereModel->vertexArray[sphereModel->indexArray[i*3]*3+1];
        curVer1.z = sphereModel->vertexArray[sphereModel->indexArray[i*3]*3+2];
        curVer2.x = sphereModel->vertexArray[sphereModel->indexArray[i*3+1]*3+0];
        curVer2.y = sphereModel->vertexArray[sphereModel->indexArray[i*3+1]*3+1];
        curVer2.z = sphereModel->vertexArray[sphereModel->indexArray[i*3+1]*3+2];
        curVer3.x = sphereModel->vertexArray[sphereModel->indexArray[i*3+2]*3+0];
        curVer3.y = sphereModel->vertexArray[sphereModel->indexArray[i*3+2]*3+1];
        curVer3.z = sphereModel->vertexArray[sphereModel->indexArray[i*3+2]*3+2];
        //out = CalcNormalVector(curVer1,curVer2,curVer3);
/*	if(DotProduct(VectorSub(curVer2, curVer1),VectorSub(curVer3,curVer1))<0){
		printf("INWARD VECTOR\n");
	}
*/
	//printf("dot=%f\n",DotProduct(VectorSub(curVer2, curVer3),VectorSub(curVer1,curVer3)));	

	out = CrossProduct(VectorSub(curVer2, curVer1), VectorSub(curVer3, curVer1));
	
	if(DotProduct(out,curVer1)<=0) {
		printf("Inward vector\n");
	}
	/*printf("Indexes %d, %d, %d\n", sphereModel->indexArray[i*3],sphereModel->indexArray[i*3+1],sphereModel->indexArray[i*3+2]);
	  printf("Normal: %f, %f, %f\n", curVer1.x, curVer1.y, curVer1.z);
	  printf("Normal: %f, %f, %f\n", curVer2.x, curVer2.y, curVer2.z);
	  printf("Normal: %f, %f, %f\n", curVer3.x, curVer3.y, curVer3.z);
	  */


	sphereModel->normalArray[sphereModel->indexArray[i*3]*3+0] += out.x;
	sphereModel->normalArray[sphereModel->indexArray[i*3]*3+1] += out.y;
	sphereModel->normalArray[sphereModel->indexArray[i*3]*3+2] += out.z;
	sphereModel->normalArray[sphereModel->indexArray[i*3+1]*3+0] += out.x;
	sphereModel->normalArray[sphereModel->indexArray[i*3+1]*3+1] += out.y;
	sphereModel->normalArray[sphereModel->indexArray[i*3+1]*3+2] += out.z;
	sphereModel->normalArray[sphereModel->indexArray[i*3+2]*3+0] += out.x;
	sphereModel->normalArray[sphereModel->indexArray[i*3+2]*3+1] += out.y;
	sphereModel->normalArray[sphereModel->indexArray[i*3+2]*3+2] += out.z;
	/*	
		sphereModel->normalArray[3*i] = out.x;
		sphereModel->normalArray[3*i+1] = out.y;
		sphereModel->normalArray[3*i+2] = out.z;
		*/	
	}
	/*GLfloat norm;
	  for(int i=0;i<sphereModel->numVertices;i++){
	  norm = sqrt(normals[i*3] * normals[i*3] + normals[i*3+1] * normals[i*3+1] + normals[i*3+2] * normals[i*3+2]);
	  printf("Norm: %f\n", norm);
	  normals[i*3] /= norm;
	  normals[i*3+1] /= norm;
	  normals[i*3+2] /= norm;
	  }*/
//	sphereModel->normalArray = normals;	
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

