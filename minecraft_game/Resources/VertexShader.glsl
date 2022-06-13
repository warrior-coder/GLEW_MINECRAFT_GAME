#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texture_coord;

out vec4 a_color;
out vec2 a_texture_coord;

uniform mat4 model_view;
uniform mat4 projection_view;

void main()
{
	a_color = vec4(1.0, 1.0, 1.0, 1.0);
	a_texture_coord = v_texture_coord;

	gl_Position = projection_view * model_view * vec4(v_position, 1.0);
}