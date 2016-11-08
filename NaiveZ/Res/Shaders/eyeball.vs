#version 330 core

layout(location = 0)in vec3 pos;
layout(location = 1)in vec2 tex;

uniform mat4 MVP;

out vec2 texOut;

void main()
{
	gl_Position = MVP * vec4(pos,1);
	texOut = tex;
}