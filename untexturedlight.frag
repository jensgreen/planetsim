#version 150
out vec4 outColor;

in vec3 exNormal;
in vec3 exPosition;


void main(void)
{	
	float diffuse, ambient = 0.0;
	float shade = 0;
	vec3 lightPos = vec3(0);
  vec3 color = vec3(1);
  vec3 lightDir;

  color = vec3(0);


  // calc the vector light to vertice
  lightDir = lightPos - exPosition;

  // Diffuse
  diffuse = dot(normalize(exNormal), normalize(lightDir));
  diffuse = max(0.0, diffuse); // No negative light	
  color += ambient+0.5*diffuse*color;	
  outColor = vec4(color, 1.0);

}

