#pragma once

#include <string>

#include <GLEW/glew.h>

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