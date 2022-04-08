#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


struct GLFWwindow;

class Window
{
public:
	static GLFWwindow* _window;

	static int Initialize(int width, int height, const char* title = "");
	static 	void Terminate();

	static bool ShouldClose();
	static void SwapBuffers();

	static void SetShouldClose(int flag);
};