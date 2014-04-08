#version 150

uniform mat4 totalMatrix;

in vec3 inPosition;
in vec2 inTexCoord;

out vec2 texCoord;

void main(void)
{
  gl_Position = totalMatrix * vec4(inPosition, 1.0);
  texCoord = inTexCoord;
}