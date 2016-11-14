#version 330 core

in vec2 texOut;
in vec3 posW;
in vec3 normalOutW;

uniform sampler2D kdSampler2D; 
uniform int UseTex;

uniform vec3 SunLightDirW;
uniform vec3 SunLightColor;

out vec4 color;

void main()
{
	if(UseTex == 1)
	{
		vec3 p = posW;
		vec3 n = normalOutW;
		color = texture(kdSampler2D, texOut);
	}
	else
		color = vec4(1.0,1.0,1.0,1.0);
}