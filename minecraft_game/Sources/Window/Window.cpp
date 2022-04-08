#include "Window.hpp"


GLFWwindow* Window::_window;

int Window::Initialize(int width, int height, const char* title)
{
    // initialize the library
    if (!glfwInit())
    {
        return 1;
    }

    // create a windowed mode window and its OpenGL context
    _window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!_window)
    {
        glfwTerminate();
        return 1;
    }

    // make the window's context current
    glfwMakeContextCurrent(_window);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return 2;
    }

    return 0;
}

void Window::Terminate()
{
    glfwTerminate();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(_window);
}

void Window::SetShouldClose(int flag)
{
    glfwSetWindowShouldClose(_window, flag);
}
