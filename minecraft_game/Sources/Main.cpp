#include <iostream>

#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Graphics/Shader.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void)
{
    Window::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Voxel Engine");
    Events::Initialize();

    // .glslv Ц OpenGL Shading Language Vertex
    // .glslf Ц OpenGL Shading Language Fragment
    Shader* shader = LoadShader("Resources/main.glslv", "Resources/main.glslf");
    if (!shader)
    {
        std::cerr << "FAILED_TO_LOAD_SHADER" << std::endl;
        Window::Terminate();
        return 3;
    }

   
    // массив координат вершин
    const GLfloat vertices[] = {
        0, 0, 0,
        1, 0, 0,
        0, 1, 0
    };
    GLuint vertexArrayId, vertexBufferId;

    glGenVertexArrays(1, &vertexArrayId); // создаем объект вершинного массива (VAO)
    glGenBuffers(1, &vertexBufferId); // создаем объект вершинного буфера (VBO)

	glBindVertexArray(vertexArrayId); // прив€зываем VAO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId); // прив€зываем VBO к VAO

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // копируем массив вершин в VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL); // указываем вершинные атрибуты дл€ VAO
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // отв€зываем вершинный массив

    // очистка изображени€
    glClearColor(0, 1, 0, 1);

    // основной цикл программы
    while (!Window::ShouldClose())
    {
        // запрос и обработка событий
        Events::PollEvents();

        if (Events::KeyJustPressed(GLFW_KEY_ESCAPE))
        {
            Window::SetShouldClose(true);
        }
        if (Events::MouseJustClicked(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(1, 0, 0, 1);
        }

        // очистка изображени€
        glClear(GL_COLOR_BUFFER_BIT);

    	// отрисовка VAO
        shader->Use();
        glBindVertexArray(vertexArrayId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);


        // обмен переднего и заднего буферов
        Window::SwapBuffers();
    }

    delete shader;
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteVertexArrays(1, &vertexArrayId);
    Window::Terminate();

    return 0;
}