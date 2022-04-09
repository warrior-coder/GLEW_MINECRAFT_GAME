#include "Window.hpp"


GLFWwindow* Window::window;


int Window::Initialize(const int width, const int height, const char* title)
{
    // initialize the library
    if (!glfwInit())
    {
        return 1;
    }

    // create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    // make the window's context current
    glfwMakeContextCurrent(window);

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
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::SetShouldClose(int flag)
{
    glfwSetWindowShouldClose(window, flag);
}
