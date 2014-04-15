#version 150
out vec4 outColor;

const int NR_OF_LIGHTSOURCES = 1;

in vec3 exNormal;
in vec3 exPosition;

uniform vec3 lightSourcesPos[NR_OF_LIGHTSOURCES];
uniform vec3 lightSourcesColor[NR_OF_LIGHTSOURCES];


void main(void)
{	
	float diffuse, ambient = 0.0;
	float shade;
	vec3 lightColor, lightPos, lightDir, color;

	color.x = 0;
	color.y = 0;
	color.z = 0;


	for(int i = 0; i < NR_OF_LIGHTSOURCES;i++){
		lightColor = lightSourcesColor[i];	
		// calc the vector light to vertice
		lightDir = lightSourcesPos[i] - exPosition;

		// Diffuse
		diffuse = dot(normalize(exNormal), normalize(lightDir));
		diffuse = max(0.0, diffuse); // No negative light	
		color = ambient+0.5*diffuse*lightSourcesColor[i];	
	}
	outColor = vec4(color, 1.0);

}

