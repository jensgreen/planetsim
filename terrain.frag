#version 150

out vec4 outColor;
in vec2 texCoord;
in vec3 exNormal;
uniform sampler2D tex;

void main(void)
{
	const vec3 light = vec3(0.58, 0.58, 0.58);
	float diffuse;
	// Diffuse
	diffuse = dot(normalize(exNormal), light);
	diffuse = max(0.0, diffuse); // No negative light	
	outColor =vec4(diffuse,diffuse,diffuse, 1.0); //vec4(1.0, 0.0, 0.0, 1.0);//texture(tex, texCoord);
}
