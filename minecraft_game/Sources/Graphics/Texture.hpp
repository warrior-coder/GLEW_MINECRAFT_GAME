#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


class Texture
{
public:
	GLuint textureId;
	GLuint width;
	GLuint height;

	explicit Texture(GLuint textureId, GLuint width, GLuint height);
	~Texture();

	void Bind();
};

extern Texture* LoadTexture(const std::string& fileName);