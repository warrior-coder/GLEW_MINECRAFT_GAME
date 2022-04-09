#include "Shader.hpp"

Shader::Shader(GLuint programId)
	: programId(programId)
{

}

Shader::~Shader()
{
	glDeleteProgram(programId);
}

void Shader::Use()
{
	glUseProgram(programId);
}

Shader* LoadShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName)
{
	// ������ ����� �������� �� ������
	std::string vertexShaderCode;
	std::string fragmentShaderCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	vertexShaderFile.exceptions(std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		vertexShaderFile.open(vertexShaderFileName);
		fragmentShaderFile.open(fragmentShaderFileName);

		std::stringstream vertexShaderStream;
		std::stringstream fragmentShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexShaderCode = vertexShaderStream.str();
		fragmentShaderCode = fragmentShaderStream.str();

	}
	catch (const std::ifstream::failure& exception)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		return nullptr;
	}

	// �������� �-������ � ������ ��������
	const GLchar* c_vertexShaderCode = vertexShaderCode.c_str();
	const GLchar* c_fragmentShaderCode = fragmentShaderCode.c_str();

	GLuint vertexShaderId;
	GLuint fragmentShaderId;
	GLint success;
	GLchar infoLog[512];

	// ������� � ����������� ��������� ������
	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &c_vertexShaderCode, NULL);
	glCompileShader(vertexShaderId);
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED" << std::endl;
		return nullptr;
	}

	// ������� � ����������� ����������� ������
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &c_fragmentShaderCode, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED" << std::endl;
		return nullptr;
	}

	// ������� � ������� ��������� ���������
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED" << std::endl;

		// ������������ ���������� ��� ������� ������
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);

		// ������������ ���������� ��� ��������� ������
		glDeleteProgram(programId);

		return nullptr;
	}

	// ������������ ���������� ��� ������� ������
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	// ���������� ����� �������
	return new Shader(programId);
}
