#version 330 core

in vec2 texOut;
in vec3 posW;
in vec3 normalOutW;

uniform sampler2D kdSampler2D; 
uniform int UseTex;
uniform vec3 Eye;

struct Material_
{
	vec3 Diffuse;
	vec3 Specular;
};
uniform Material_ Material;

struct SunLight_
{
	vec3 Dir;
	vec3 Color;
};
uniform SunLight_ Sun;

struct PointLight_
{
	vec3 Pos;
	vec3 Color;

	float Range;
	float ConstAtten;
	float LinearAtten;
	float QuadAtten;
};
uniform PointLight_ PointLight[5];

/////// 环境光 //////
uniform vec3 ambient = vec3(0.1,0.1,0.1);



//阳光方向、阳光颜色、表面法向量
vec4 sunlight(vec3 sunDir, vec3 sunColor, vec3 normal)
{
	vec4 OUT = vec4(0,0,0,1);

	normal = normalize(normal);
	vec3 lightDir = -sunDir;
	float NoL = max(0, dot(normal, lightDir));
	vec4 diffuse = vec4(NoL * sunColor, 1);

	OUT = diffuse;
	return OUT;
}


//shading点位置、点法向量、
vec4 pointlight(vec3 posW, vec3 normalW)
{
	vec4 OUT = vec4(0,0,0,1);
	for(int i = 0; i != 5; ++i)
	{
		float dist = length(Eye - posW);
		if(dist > PointLight[i].Range)
			continue;
		vec3 view = normalize(Eye - posW);
		vec3 lightdir = normalize(PointLight[i].Pos - posW);
		vec3 half = normalize(view + lightdir);
	}
	return OUT;
}

out vec4 color;

void main()
{
	if(UseTex == 1)
	{
		vec4 sun = sunlight(Sun.Dir, Sun.Color, normalOutW);
		color = texture(kdSampler2D, texOut) * (sun + vec4(ambient, 1.0));
	}
	else
	{
		color = vec4(1.0,1.0,1.0,1.0);
	}
}