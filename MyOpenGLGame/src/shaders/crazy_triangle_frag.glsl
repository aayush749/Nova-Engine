#version 430 core


in vec3 col;
out vec4 color;

uniform float time;

void main()
{
	float scaledTime = 100.0f * time;
	color = vec4(abs(cos(col.x * scaledTime)), abs(sin(col.y * scaledTime)), col.z, 1.0);
}