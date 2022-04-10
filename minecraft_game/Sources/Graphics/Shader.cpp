#include "Shader.hpp"


Shader::Shader(GLuint programId)
	: programId(programId)
{

}

Shader::~Shader()
{
	// удаление шейдерной программы
	glDeleteProgram(programId);
}

void Shader::Use()
{
	// выполнение шейдерной программы
	glUseProgram(programId);
}