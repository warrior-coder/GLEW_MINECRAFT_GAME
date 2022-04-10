#include "Shader.hpp"


Shader::Shader(GLuint programId)
	: programId(programId)
{}

Shader::~Shader()
{
	glDeleteProgram(programId); // удаление шейдерной программы
}

void Shader::Use()
{
	glUseProgram(programId); // выполнение шейдерной программы
}