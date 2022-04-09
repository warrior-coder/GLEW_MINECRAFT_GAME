#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
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

extern Shader* LoadShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);
