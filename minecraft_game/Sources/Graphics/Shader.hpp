#pragma once

#include <string>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


class Shader
{
public:
	GLuint programId;

	explicit Shader(GLuint programId);
	~Shader();

	void Use();
};

// реализация находится во внешнем файле
extern Shader* LoadShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);