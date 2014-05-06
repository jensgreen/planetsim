#version 150

in  vec3 inPosition;
in  vec3 inNormal;
out vec3 exNormal;
out vec3 exPosition;

uniform mat4 projMatrix;
uniform mat4 mdlMatrix;

void main(void)
{
	exPosition = inPosition;
	exNormal = inNormal;
	mat3 normalMatrix1 = mat3(mdlMatrix);
	gl_Position = projMatrix * mdlMatrix * vec4(inPosition, 1.0);
}
