#version 150
out vec4 outColor;


in vec3 exNormal;
in vec3 exPosition;

uniform vec3 lightSourcesPos;
uniform vec3 lightSourcesColor;


void main(void)
{	
	float diffuse, ambient = 0.0;
	float shade = 0;
	vec3 lightDir, color = vec3(0.0, 0, 0.0);
	
	// calc the vector light to vertice
	lightDir = vec3(-1,0,0);
	// Diffuse
	diffuse = dot(normalize(exNormal), lightDir);
	//diffuse = max(0.0, diffuse); // No negative light	
	color = (ambient+0.5*diffuse)*lightSourcesColor;	
  //outColor = vec4(exPosition, 1.0);
  outColor = vec4(1.0f,0.0f,1.0f,1.0f);

}

