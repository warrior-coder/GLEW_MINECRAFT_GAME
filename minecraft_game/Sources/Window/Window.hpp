#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>


struct GLFWwindow;

// ??????? Window ???????? ?? ??????????? ????
class Window
{
public:
	static GLFWwindow* window;
	static int width;
	static int height;

	static int Initialize( int width, int height, const char* title = "GLFW Window");
	static void Terminate();

	static bool ShouldClose();
	static void SwapBuffers();

	static void SetShouldClose(int flag);
	static void SetCursorMode(int value);

	Window() = delete;
	~Window() = delete;
};