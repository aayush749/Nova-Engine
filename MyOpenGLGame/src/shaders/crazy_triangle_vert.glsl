#version 430 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 aTexCoord;

out vec3 col;
out vec2 texCoord;

uniform float time;
uniform mat4 proj;

void main()
{
	gl_Position = proj * vec4(pos.xy, 0.0, 1.0);
	col = color;
	texCoord = aTexCoord;
}