#include "Shader.hpp"


Shader::Shader(GLuint programId)
	: programId(programId)
{}

Shader::~Shader()
{
	glDeleteProgram(programId); // �������� ��������� ���������
}

void Shader::Use()
{
	glUseProgram(programId); // ���������� ��������� ���������
}

void Shader::UniformMatrix(const std::string& name, glm::mat4 matrix)
{
	GLuint transformLoc = glGetUniformLocation(programId, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}
