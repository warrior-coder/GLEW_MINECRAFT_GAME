#pragma once

#include "Window.hpp"


void MouseButtonCallback(GLFWwindow* window, int buttonIndex, int action, int mods);
void KeyCallback(GLFWwindow* window, int keyIndex, int scancode, int action, int mods);

class Events
{
public:
	static bool* _keys;
	static unsigned int* _frames;
	static unsigned int _current;
	static double deltaX, deltaY;
	static double x, y;
	static bool _cursor_locked;
	static bool _cursor_started;

	static int Initialize();
	static void Terminate();

	static void PollEvents();

	static bool pressed(int keyCode);
	static bool justPressed(int keyCode);
	static bool clicked(int keyCode);
	static bool justClicked(int keyCode);
};

