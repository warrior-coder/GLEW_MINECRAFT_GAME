#include <iostream>

#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main()
{
    Window::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Voxel Engine");
    Events::Initialize();

    // загрузка шейдеров
    Shader* shader = LoadShader("Resources/VertexShader.glsl", "Resources/FragmentShader.glsl");
    if (!shader)
    {
        std::cerr << "FAILED_TO_LOAD_SHADER" << std::endl;
        Window::Terminate();
        return 3;
    }

	Texture* texture = LoadTexture("Resources/TestImage.png");
    if (!texture)
    {
        std::cerr << "FAILED_TO_LOAD_TEXTURE" << std::endl;
        Window::Terminate();
        delete shader;
        return 4;
    }

    // создание буфера координат вершин
    const GLfloat vertexCoordinates[] = {
    //   X   Y   Z   U   V
        -1, -1,  0,  0,  0,
         1, -1,  0,  1,  0,
    	-1,  1,  0,  0,  1,

         1, -1,  0,  1,  0,
         1,  1,  0,  1,  1,
    	-1,  1,  0,  0,  1
    }; // массив координат вершин
    GLuint vertexCoordinatesBufferId;

	glGenBuffers(1, &vertexCoordinatesBufferId); // генерируем 1 буфер для VBO (Vertex Buffer Object) на видеокарте
    glBindBuffer(GL_ARRAY_BUFFER, vertexCoordinatesBufferId); // связываем vertexCoordinatesBufferId с буфером
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoordinates), vertexCoordinates, GL_STATIC_DRAW); // копируем данные vertexCoordinates из оперативной памяти в буфер на видеокарту

    // указываем вершинные атрибуты для VAO
    GLuint vertexArrayId;

    glGenVertexArrays(1, &vertexArrayId); // генерируем 1 буфер для VAO (Vertex Array Object) на видеокарте
	glBindVertexArray(vertexArrayId); // привязываем VAO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	    glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	    glEnableVertexAttribArray(1);
    glBindVertexArray(0u); // отвязываем VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0u); // отвязываемся от буфера

    // очистка изображения
    glClearColor(0.5f, 0.5f, 0.5f, 1);

    // включение смешивания для корректной прозрачности
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
            glClearColor(0, 0, 0, 1);
        }

        // очистка изображения
        glClear(GL_COLOR_BUFFER_BIT);

    	// отрисовка VAO
        shader->Use();
        texture->Bind();
		
        glBindVertexArray(vertexArrayId);
			glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0u);

        // обмен переднего и заднего буферов
        Window::SwapBuffers();
    }

    // освобождение памяти
    delete shader;
    delete texture;
    glDeleteBuffers(1, &vertexCoordinatesBufferId); // удаление вершинного буфера
    glDeleteVertexArrays(1, &vertexArrayId); // удаление вершинного массива
    Window::Terminate();

    return 0;
}