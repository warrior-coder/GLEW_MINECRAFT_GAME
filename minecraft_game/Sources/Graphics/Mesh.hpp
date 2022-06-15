#pragma once

#include <GLEW/glew.h>

class Mesh
{
	GLuint VAO;
	GLuint VBO;
	size_t vertices;

public:
	Mesh(const GLfloat* buffer, size_t vertices, const GLint* attributes);
	~Mesh();

	void Draw(GLenum mode);

};

