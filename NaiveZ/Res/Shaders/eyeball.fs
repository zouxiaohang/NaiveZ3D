#version 330 core

in vec2 texOut;

uniform sampler2D kdSampler2D; 

out vec4 color;

void main()
{
	color = texture(kdSampler2D, texOut);
}