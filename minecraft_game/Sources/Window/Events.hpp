#pragma once

#include "Window.hpp"


void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int buttonCode, int action, int mods);
void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos);


class Events
{
public:
	static bool* keys;
	static unsigned int* frames;
	static unsigned int current;
	static double deltaX;
	static double deltaY;
	static double x;
	static double y;
	static bool cursorLocked;
	static bool cursorStarted;

	static int Initialize();
	static void Terminate();

	static void PollEvents();

	static bool KeyPressed(int keyCode);
	static bool KeyJustPressed(int keyCode);
	static bool MouseClicked(int buttonCode);
	static bool MouseJustClicked(int buttonCode);
};