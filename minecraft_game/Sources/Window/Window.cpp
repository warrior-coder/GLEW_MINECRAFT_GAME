#include "Window.hpp"


// определяем static-члены класса Window
GLFWwindow* Window::window;
int Window::width;
int Window::height;

int Window::Initialize(const int width, const int height, const char* title)
{
    // инициализация GLFW
    if (!glfwInit())
    {
        return 1;
    }


    // устанавливаем параметры окна
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // пункт версии OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // подпункт версии OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // для какого профиля OpenGL создается контекст
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); // размер окна может изменяться


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

    glViewport(0, 0, width, height);
    Window::width = width;
    Window::height = height;

    return 0;
}

void Window::Terminate()
{
    glfwTerminate(); // завершает работу GLFW и освобождает всю выделенную им память
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

void Window::SetCursorMode(int value)
{
    glfwSetInputMode(window, GLFW_CURSOR, value);
}
