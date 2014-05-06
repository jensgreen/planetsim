#version 150
out vec4 outColor;

in vec3 exNormal;

void main(void)
{	
	const vec3 light = vec3(0.5, 0.5, 0.0);
	float diffuse, ambient = 0.0;
	// Diffuse
	diffuse = dot(normalize(exNormal), light);
	diffuse = max(0.0, diffuse); // No negative light	
	float shade = ambient+1.0*diffuse;	
	outColor =vec4(shade, shade,shade, 1.0);
}

