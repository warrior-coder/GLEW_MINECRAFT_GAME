#version 330 core

in vec4 a_color;
in vec2 a_texture_coord;

out vec4 f_color;

uniform sampler2D u_texture;

void main()
{
	f_color = a_color * texture(u_texture, a_texture_coord);
}