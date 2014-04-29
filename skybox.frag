#version 150

uniform sampler2D texUnit;
in vec2 texCoord;
out vec4 out_Color;

void main(void)
{
  // out_Color = vec4(1.0, 1.0, 1.0, 1.0);
  out_Color = texture(texUnit, texCoord); 
}
