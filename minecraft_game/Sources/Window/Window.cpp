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
    glfwMakeContextCurrent(window); // делаем контекст окна текущим контекстом отрисовки

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
    glfwTerminate(); // завершает работу GLFW и освобождает всю выделенную ей память
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window); // обмен переднего и заднего буферов
}

void Window::SetShouldClose(int flag)
{
    glfwSetWindowShouldClose(window, flag);
}
