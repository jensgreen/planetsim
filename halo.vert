#version 150

in  vec3 inPosition;
in  vec2 inTexCoord;
out vec3 exPosition;
out  vec2 exTexCoord;

uniform mat4 projMatrix;
uniform mat4 mdlMatrix;

void main(void)
{
	exTexCoord = inTexCoord;
	gl_Position = projMatrix * mdlMatrix * vec4(inPosition, 1.0);
}
