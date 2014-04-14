#version 150
out vec4 outColor;

in vec3 exNormal;
in vec3 exPosition;

uniform vec3 lightSourcesPos[1];
uniform vec3 lightSourcesColor[1];

void main(void)
{	
	vec3 lightColor, lightPos;
	for(int i = 0; i < 1;i++){
		lightColor = lightSourcesColor[i];	
		ligthPos = lightSourcesPos[i];
		// calc the vector light to vertice
	}
	float diffuse, ambient = 0.0;
	// Diffuse
	diffuse = dot(normalize(exNormal), light);
	diffuse = max(0.0, diffuse); // No negative light	
	float shade = ambient+1.0*diffuse;	
	outColor =vec4(shade, shade/6,shade/2, 1.0);
}

