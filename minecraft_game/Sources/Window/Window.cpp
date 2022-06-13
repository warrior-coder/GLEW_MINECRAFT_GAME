#include "Window.hpp"


// ���������� static-����� ������ Window
GLFWwindow* Window::window;
int Window::width;
int Window::height;

int Window::Initialize(const int width, const int height, const char* title)
{
    // ������������� GLFW
    if (!glfwInit())
    {
        return 1;
    }


    // ������������� ��������� ����
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ����� ������ OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // �������� ������ OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ��� ������ ������� OpenGL ��������� ��������
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // ������ ���� ����� ����������


    // �������� ���� � ���������� OpenGL
	window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window); // ������ �������� ���� ������� ���������� ���������

    // ������������� GLEW (������ ����� ����������� ��������� ��������� OpenGL)
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return 3;
    }

    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;

    return 0;
}

void Window::Terminate()
{
    glfwTerminate(); // ��������� ������ GLFW � ����������� ��� ���������� �� ������
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window); // ����� ��������� � ������� �������
}

void Window::SetShouldClose(int flag)
{
    glfwSetWindowShouldClose(window, flag);
}

void Window::SetCursorMode(int value)
{
    glfwSetInputMode(window, GLFW_CURSOR, value);
}
