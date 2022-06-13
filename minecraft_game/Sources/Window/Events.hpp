#pragma once

#include "Window.hpp"


// функции-обработчики событий окна
void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int buttonCode, int action, int mods);
void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

// подсистема Events отвечает за события графическое окна
class Events
{
public:
	static bool* keys;

	static unsigned int* frames;
	static unsigned int currentFrame;

	static double cursorDeltaX;
	static double cursorDeltaY;
	static double cursorX;
	static double cursorY;
	static bool cursorLocked;
	static bool cursorStarted;

	static int Initialize();
	static void Terminate();

	static void PollEvents();

	static bool KeyPressed(int keyCode);
	static bool KeyJustPressed(int keyCode);
	static bool MouseClicked(int buttonCode);
	static bool MouseJustClicked(int buttonCode);

	static void ToggleCursor();

	Events() = delete;
	~Events() = delete;
};