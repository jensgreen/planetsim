#version 150

in vec2 exTexCoord;
out vec4 outColor;

void main(void)
{
	float x = exTexCoord.x;
	float y = exTexCoord.y - 1; //y tex coords are offset in model, compensate here
	float alpha = 1-abs(x*x + y*y);
	outColor = vec4(1,1,1,alpha);
}

