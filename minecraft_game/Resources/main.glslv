#version 330 core

layout (location = 0) in vec3 v_position;

out vec4 a_color;

void main()
{
	a_color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	gl_Position = vec4(v_position, 1.0);
}