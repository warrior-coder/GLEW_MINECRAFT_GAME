#include "Window.hpp"


// определяем static-члены класса Window
GLFWwindow* Window::window;

int Window::Initialize(const int width, const int height, const char* title)
{
    // инициализация GLFW
    if (!glfwInit())
    {
        return 1;
    }

    // создание окна с контекстом OpenGL
	window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return 2;
    }

    // делаем контекст окна текущим контекстом отрисовки
    glfwMakeContextCurrent(window);

    // инициализация GLEW (только после подключения контекста отрисовки OpenGL)
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return 3;
    }

    return 0;
}

void Window::Terminate()
{
    // завершает работу GLFW и освобождает всю выделенную ей память
    glfwTerminate();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
    // меняет местами передний и задний буферы окна при отрисовки
    glfwSwapBuffers(window);
}

void Window::SetShouldClose(int flag)
{
    glfwSetWindowShouldClose(window, flag);
}
