#version 150
out vec4 outColor;


in vec3 exNormal;
in mat4 exPosition;

uniform vec3 lightSourcesPos;
uniform vec3 lightSourcesColor;


void main(void)
{	
	float diffuse, ambient = 0.0;
	float shade = 0;
	vec3 lightPos, lightDir, color;
	
	
	color = vec3(0);
	// calc the vector light to vertice
	lightDir = lightSourcesPos;
	// Diffuse
	diffuse = dot(normalize(exNormal), normalize(lightDir));
	diffuse = max(0.0, diffuse); // No negative light	
	color += (ambient+0.5*diffuse)*lightSourcesColor;	
	outColor = vec4(color, 1.0);

}

