#version 330 core

layout(location = 0)in vec3 pos;
layout(location = 1)in vec2 tex;
layout(location = 2)in vec3 normal;

uniform mat4 M;
uniform mat4 M_Normal;
uniform mat4 MVP;

out vec2 texOut;
out vec3 posW;
out vec3 normalOutW;

void main()
{
	posW = (M * vec4(pos, 1)).xyz;
	texOut = vec2(tex.x, 1.0 - tex.y);
	normalOutW = (M_Normal * vec4(normal, 0)).xyz;

	gl_Position = MVP * vec4(pos,1);
}