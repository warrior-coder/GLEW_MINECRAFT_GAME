#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texture_coord;
layout (location = 2) in float v_light;

out vec4 a_color;
out vec2 a_texture_coord;

uniform mat4 model_view;
uniform mat4 projection_view;

void main()
{
	a_color = vec4(v_light, v_light, v_light, 1.0f);
	a_texture_coord = v_texture_coord;

	gl_Position = projection_view * model_view * vec4(v_position, 1.0f);
}