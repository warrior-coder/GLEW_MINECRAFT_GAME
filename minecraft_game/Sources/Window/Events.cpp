#include "Events.hpp"


bool* Events::_keys;
unsigned int* Events::_frames;
unsigned int Events::_current;
double Events::deltaX;
double Events::deltaY;
double Events::x;
double Events::y;
bool Events::_cursor_locked;
bool Events::_cursor_started;

#define KEYS_SIZE 1032
#define MOUSE_BUTTON_OFFSET 1024


void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Events::_keys[keyCode] = true;
		Events::_frames[keyCode] = Events::_current;
	}
	else if (action == GLFW_RELEASE)
	{
		Events::_keys[keyCode] = false;
		Events::_frames[keyCode] = Events::_current;
	}
}

void MouseButtonCallback(GLFWwindow* window, int buttonCode, int action, int mods)
{
	int keyCode = MOUSE_BUTTON_OFFSET + buttonCode;

	if (action == GLFW_PRESS)
	{
		Events::_keys[keyCode] = true;
		Events::_frames[keyCode] = Events::_current;
	}
	else if (action == GLFW_RELEASE)
	{
		Events::_keys[keyCode] = false;
		Events::_frames[keyCode] = Events::_current;
	}
}

void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (Events::_cursor_started)
	{
		Events::deltaX += xPos - Events::x;
		Events::deltaY += yPos - Events::y;
	}
	else
	{
		Events::_cursor_started = true;
	}

	Events::x = xPos;
	Events::y = yPos;
}

int Events::Initialize()
{
	GLFWwindow* window = Window::_window;

	_keys = new bool[1032]{};
	_frames = new unsigned int[1032]{};
	_current = 0;
	deltaX = 0.0;
	deltaY = 0.0;
	x = 0.0;
	y = 0.0;
	_cursor_locked = false;
	_cursor_started = false;

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);

	return 0;
}

void Events::Terminate()
{
	delete[] _keys;
	delete[] _frames;
}

void Events::PollEvents()
{
	_current++;
	deltaX = 0.0;
	deltaY = 0.0;

	glfwPollEvents();
}

bool Events::pressed(int keyCode)
{
	if (keyCode < 0 || keyCode >= MOUSE_BUTTON_OFFSET) return false;

	return _keys[keyCode];
}

bool Events::justPressed(int keyCode)
{
	if (keyCode < 0 || keyCode >= MOUSE_BUTTON_OFFSET) return false;

	return _keys[keyCode] && _frames[keyCode] == _current;
}

bool Events::clicked(int buttonCode)
{
	int keyCode = MOUSE_BUTTON_OFFSET + buttonCode;
	if (keyCode < MOUSE_BUTTON_OFFSET || keyCode >= KEYS_SIZE) return false;

	return _keys[keyCode];
}

bool Events::justClicked(int buttonCode)
{
	int keyCode = MOUSE_BUTTON_OFFSET + buttonCode;
	if (keyCode < MOUSE_BUTTON_OFFSET || keyCode >= KEYS_SIZE) return false;

	return _keys[keyCode] && _frames[keyCode] == _current;
}
