#version 330 core

in vec2 texOut;

uniform sampler2D kdSampler2D; 
uniform int UseTex;

out vec4 color;

void main()
{
	if(UseTex == 1)
		color = texture(kdSampler2D, texOut);
	else
		color = vec4(1.0,1.0,1.0,1.0);
}