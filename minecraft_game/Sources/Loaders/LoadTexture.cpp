#include "LoadTexture.hpp"


Texture* LoadTexture(const std::string& fileName)
{
    GLuint width;
	GLuint height;
    GLuint textureId = c_load_png(fileName.c_str(), &width, &height);

    if (!textureId)
    {
        std::cerr << "LOAD_TEXTURE_ERROR: " << fileName << std::endl;
        return nullptr;
    }

	return new Texture(textureId, width, height);
}