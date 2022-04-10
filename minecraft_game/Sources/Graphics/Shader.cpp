#include "Shader.hpp"


Shader::Shader(GLuint programId)
	: programId(programId)
{

}

Shader::~Shader()
{
	// �������� ��������� ���������
	glDeleteProgram(programId);
}

void Shader::Use()
{
	// ���������� ��������� ���������
	glUseProgram(programId);
}