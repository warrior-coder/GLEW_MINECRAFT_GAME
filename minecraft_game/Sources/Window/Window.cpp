#include "Window.hpp"


// ���������� static-����� ������ Window
GLFWwindow* Window::window;

int Window::Initialize(const int width, const int height, const char* title)
{
    // ������������� GLFW
    if (!glfwInit())
    {
        return 1;
    }

    // �������� ���� � ���������� OpenGL
	window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return 2;
    }

    // ������ �������� ���� ������� ���������� ���������
    glfwMakeContextCurrent(window);

    // ������������� GLEW (������ ����� ����������� ��������� ��������� OpenGL)
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return 3;
    }

    return 0;
}

void Window::Terminate()
{
    // ��������� ������ GLFW � ����������� ��� ���������� �� ������
    glfwTerminate();
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
    // ������ ������� �������� � ������ ������ ���� ��� ���������
    glfwSwapBuffers(window);
}

void Window::SetShouldClose(int flag)
{
    glfwSetWindowShouldClose(window, flag);
}
