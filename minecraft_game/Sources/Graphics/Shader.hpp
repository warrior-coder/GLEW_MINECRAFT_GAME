#pragma once

#include <string>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>


class Shader
{
public:
	GLuint programId;

	explicit Shader(GLuint programId);
	~Shader();

	void Use();
	void UniformMatrix(const std::string& name, glm::mat4 matrix);
};

// реализация находится во внешнем файле
extern Shader* LoadShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);