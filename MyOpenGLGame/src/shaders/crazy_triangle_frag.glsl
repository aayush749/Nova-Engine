#version 430 core


in vec3 col;
in vec2 texCoord;

out vec4 color;

uniform float time;

uniform sampler2D samp;

void main()
{
	float scaledTime = 100.0f * time;
	color = vec4(abs(cos(col.x * scaledTime)), abs(sin(col.y * scaledTime)), col.z, 1.0);
	color *= texture(samp, texCoord);
}