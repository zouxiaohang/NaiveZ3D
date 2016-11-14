#version 330 core

in vec2 texOut;
in vec3 posW;
in vec3 normalOutW;

uniform sampler2D kdSampler2D; 
uniform int UseTex;

uniform vec3 SunLightDirW;
uniform vec3 SunLightColor;

uniform vec3 ambient = vec3(0.2,0.2,0.2);

out vec4 color;

void main()
{
	if(UseTex == 1)
	{
		vec3 lightDir = -SunLightDirW;
		float NoL = max(0, dot(normalOutW, lightDir));
		vec4 diffuse = vec4(NoL * SunLightColor, 1);
		color = texture(kdSampler2D, texOut) * (diffuse + vec4(ambient, 1.0));
	}
	else
		color = vec4(1.0,1.0,1.0,1.0);
}