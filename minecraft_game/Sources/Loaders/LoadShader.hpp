#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "../Graphics/Shader.hpp"


class Shader;

Shader* LoadShader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);