#pragma once

#include <iostream>
#include <string>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <png.h>

#include "../Graphics/Texture.hpp"


class Texture;

Texture* LoadTexture(const std::string& fileName);
