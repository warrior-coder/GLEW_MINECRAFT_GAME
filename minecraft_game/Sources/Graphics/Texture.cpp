#include "Texture.hpp"

Texture::Texture(GLuint textureId, GLuint width, GLuint height)
	: textureId(textureId)
	, width(width)
	, height(height)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}