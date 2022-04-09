#include "Events.hpp"


bool* Events::keys;
unsigned int* Events::frames;
unsigned int Events::current;
double Events::deltaX;
double Events::deltaY;
double Events::x;
double Events::y;
bool Events::cursorLocked;
bool Events::cursorStarted;


#define KEYS_SIZE 1032
#define MOUSE_BUTTON_CODE_OFFSET 1024


void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Events::keys[keyCode] = true;
		Events::frames[keyCode] = Events::current;
	}
	else if (action == GLFW_RELEASE)
	{
		Events::keys[keyCode] = false;
		Events::frames[keyCode] = Events::current;
	}
}

void MouseButtonCallback(GLFWwindow* window, int buttonCode, int action, int mods)
{
	const int keyCode = MOUSE_BUTTON_CODE_OFFSET + buttonCode;

	if (action == GLFW_PRESS)
	{
		Events::keys[keyCode] = true;
		Events::frames[keyCode] = Events::current;
	}
	else if (action == GLFW_RELEASE)
	{
		Events::keys[keyCode] = false;
		Events::frames[keyCode] = Events::current;
	}
}

void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (Events::cursorStarted)
	{
		Events::deltaX += xPos - Events::x;
		Events::deltaY += yPos - Events::y;
	}
	else
	{
		Events::cursorStarted = true;
	}

	Events::x = xPos;
	Events::y = yPos;
}

int Events::Initialize()
{
	GLFWwindow* window = Window::window;

	keys = new bool[1032]{};
	frames = new unsigned int[1032]{};
	current = 0;
	deltaX = 0.0;
	deltaY = 0.0;
	x = 0.0;
	y = 0.0;
	cursorLocked = false;
	cursorStarted = false;

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);

	return 0;
}

void Events::Terminate()
{
	delete[] keys;
	delete[] frames;
}

void Events::PollEvents()
{
	current++;
	deltaX = 0.0;
	deltaY = 0.0;

	glfwPollEvents();
}

bool Events::KeyPressed(int keyCode)
{
	if (keyCode < 0 || keyCode >= MOUSE_BUTTON_CODE_OFFSET) return false;

	return keys[keyCode];
}

bool Events::KeyJustPressed(int keyCode)
{
	if (keyCode < 0 || keyCode >= MOUSE_BUTTON_CODE_OFFSET) return false;

	return keys[keyCode] && frames[keyCode] == current;
}

bool Events::MouseClicked(int buttonCode)
{
	const int keyCode = MOUSE_BUTTON_CODE_OFFSET + buttonCode;

	if (keyCode < MOUSE_BUTTON_CODE_OFFSET || keyCode >= KEYS_SIZE) return false;

	return keys[keyCode];
}

bool Events::MouseJustClicked(int buttonCode)
{
	const int keyCode = MOUSE_BUTTON_CODE_OFFSET + buttonCode;

	if (keyCode < MOUSE_BUTTON_CODE_OFFSET || keyCode >= KEYS_SIZE) return false;

	return keys[keyCode] && frames[keyCode] == current;
}
