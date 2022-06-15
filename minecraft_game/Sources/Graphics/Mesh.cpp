#include "Mesh.hpp"


Mesh::Mesh(const GLfloat* arrayBuffer, size_t vertices, const GLint* attributes)
	: vertices(vertices)
{
	int vertexSize = 0;
	for (int i = 0; attributes[i]; ++i)
	{
		vertexSize += attributes[i];
	}

	glGenVertexArrays(1, &VAO); // генерируем 1 буфер дл€ VAO (Vertex Array Object) на видеокарте
	glGenBuffers(1, &VBO); // генерируем 1 буфер дл€ VBO (Vertex Buffer Object) на видеокарте

	glBindVertexArray(VAO); // прив€зываем VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // св€зываем vertexCoordinatesBufferId с буфером
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * vertexSize * vertices,
		arrayBuffer,
		GL_STATIC_DRAW
	); // копируем данные vertexCoordinates из оперативной пам€ти в буфер на видеокарту

	int offset = 0;
	for (int i = 0; attributes[i]; ++i)
	{
		int size = attributes[i];
		glVertexAttribPointer(
			i,
			size,
			GL_FLOAT,
			GL_FALSE,
			sizeof(GLfloat) * vertexSize,
			(GLvoid*)(sizeof(GLfloat) * offset)
		);
		glEnableVertexAttribArray(i);
		offset += size;
	}

	glBindVertexArray(0u); // отв€зываем VAO
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VAO); // удаление вершинного буфера
	glDeleteVertexArrays(1, &VBO); // удаление вершинного массива
}

void Mesh::Draw(GLenum mode)
{
	glBindVertexArray(VAO);
		glDrawArrays(mode, 0, vertices);
	glBindVertexArray(0u);
}
