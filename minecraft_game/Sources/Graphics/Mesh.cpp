#include "Mesh.hpp"


Mesh::Mesh(const GLfloat* arrayBuffer, size_t vertices, const GLint* attributes)
	: vertices(vertices)
{
	int vertexSize = 0;
	for (int i = 0; attributes[i]; ++i)
	{
		vertexSize += attributes[i];
	}

	glGenVertexArrays(1, &VAO); // ���������� 1 ����� ��� VAO (Vertex Array Object) �� ����������
	glGenBuffers(1, &VBO); // ���������� 1 ����� ��� VBO (Vertex Buffer Object) �� ����������

	glBindVertexArray(VAO); // ����������� VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ��������� vertexCoordinatesBufferId � �������
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * vertexSize * vertices,
		arrayBuffer,
		GL_STATIC_DRAW
	); // �������� ������ vertexCoordinates �� ����������� ������ � ����� �� ����������

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

	glBindVertexArray(0u); // ���������� VAO
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &VAO); // �������� ���������� ������
	glDeleteVertexArrays(1, &VBO); // �������� ���������� �������
}

void Mesh::Draw(GLenum mode)
{
	glBindVertexArray(VAO);
		glDrawArrays(mode, 0, vertices);
	glBindVertexArray(0u);
}
