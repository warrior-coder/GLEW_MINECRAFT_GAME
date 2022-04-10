#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


struct GLFWwindow;

// система Window отвечает за графическое окно
class Window
{
public:
	static GLFWwindow* window;

	static int Initialize(const int width, const int height, const char* title = "GLFW Window");
	static 	void Terminate();

	static bool ShouldClose();
	static void SwapBuffers();

	static void SetShouldClose(int flag);

	Window() = delete;
	~Window() = delete;
};