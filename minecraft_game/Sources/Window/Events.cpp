#include "Events.hpp"


// определяем static-члены класса Events
bool* Events::keys;

unsigned int* Events::frames;
unsigned int Events::currentFrame;

double Events::cursorDeltaX;
double Events::cursorDeltaY;
double Events::cursorX;
double Events::cursorY;
bool Events::cursorLocked;
bool Events::cursorStarted;


#define KEYS_SIZE 1032
#define MOUSE_BUTTON_CODE_OFFSET 1024


// функция-обработчик нажатий клавиш клавиатуры
void KeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		Events::keys[keyCode] = true;
		Events::frames[keyCode] = Events::currentFrame;
	}
	else if (action == GLFW_RELEASE)
	{
		Events::keys[keyCode] = false;
		Events::frames[keyCode] = Events::currentFrame;
	}
}

// функция-обработчик нажатий клавиш мыши
void MouseButtonCallback(GLFWwindow* window, int buttonCode, int action, int mods)
{
	const int keyCode = MOUSE_BUTTON_CODE_OFFSET + buttonCode;

	if (action == GLFW_PRESS)
	{
		Events::keys[keyCode] = true;
		Events::frames[keyCode] = Events::currentFrame;
	}
	else if (action == GLFW_RELEASE)
	{
		Events::keys[keyCode] = false;
		Events::frames[keyCode] = Events::currentFrame;
	}
}

// функция-обработчик изменения позиции курсора
void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (Events::cursorStarted)
	{
		Events::cursorDeltaX += xPos - Events::cursorX;
		Events::cursorDeltaY += yPos - Events::cursorY;
	}
	else
	{
		Events::cursorStarted = true;
	}

	Events::cursorX = xPos;
	Events::cursorY = yPos;
}

// функция-обработчик изменения размера окна
void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Window::width = width;
	Window::height = height;
}

int Events::Initialize()
{
	GLFWwindow* window = Window::window;

	keys = new bool[1032]{};
	frames = new unsigned int[1032]{};
	currentFrame = 0;
	cursorDeltaX = 0.0;
	cursorDeltaY = 0.0;
	cursorX = 0.0;
	cursorY = 0.0;
	cursorLocked = false;
	cursorStarted = false;

	// устанавливаем функции-обработчики событий окна
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);

	return 0;
}

void Events::Terminate()
{
	delete[] keys;
	delete[] frames;
}

void Events::PollEvents()
{
	currentFrame++;
	cursorDeltaX = 0.0;
	cursorDeltaY = 0.0;

	// запрос событий
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

	return keys[keyCode] && frames[keyCode] == currentFrame;
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

	return keys[keyCode] && frames[keyCode] == currentFrame;
}
