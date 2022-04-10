#pragma once

#include <iostream>
#include <string>

#include <GLEW/glew.h>
#include <png.h>

#include "../Graphics/Texture.hpp"


// ���������� ������� �������� �� �
extern "C" {
	GLuint c_load_png(const char* fileName, GLuint* width_ptr, GLuint* height_ptr);
}

class Texture;

Texture* LoadTexture(const std::string& fileName);
