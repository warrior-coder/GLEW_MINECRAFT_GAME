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

    // .glsl � OpenGL Shading Language (���� ��������)
    Shader* shader = LoadShader("Resources/vertex.glsl", "Resources/fragment.glsl");
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

	// ������ ��������� ������
    constexpr GLfloat vertices[] = {
    //   X   Y   Z   U   V
        -1, -1,  0,  0,  0,
         1, -1,  0,  1,  0,
    	-1,  1,  0,  0,  1,

         1, -1,  0,  1,  0,
         1,  1,  0,  1,  1,
    	-1,  1,  0,  0,  1
    };
    GLuint vertexArrayId, vertexBufferId;

    glGenVertexArrays(1, &vertexArrayId); // ������� ������ ���������� ������� (VAO)
	glGenBuffers(1, &vertexBufferId); // ������� ������ ���������� ������ (VBO)

	glBindVertexArray(vertexArrayId); // ����������� VAO
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId); // ����������� VBO � VAO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // �������� ������ ������ � VBO

    // ��������� ��������� �������� ��� VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // ���������� ��������� ������

    // ������� �����������
    glClearColor(0.5f, 0.5f, 0.5f, 1);

    // ��������� ���������� ��� ���������� ������������
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // �������� ���� ���������
    while (!Window::ShouldClose())
    {
        // ������ � ��������� �������
        Events::PollEvents();

        if (Events::KeyJustPressed(GLFW_KEY_ESCAPE))
        {
            Window::SetShouldClose(true);
        }
        if (Events::MouseJustClicked(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(0, 0, 0, 1);
        }

        // ������� �����������
        glClear(GL_COLOR_BUFFER_BIT);

    	// ��������� VAO
        shader->Use();
        texture->Bind();
        glBindVertexArray(vertexArrayId);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // ����� ��������� � ������� �������
        Window::SwapBuffers();
    }

    // ������������ ������
    delete shader;
    delete texture;
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteVertexArrays(1, &vertexArrayId);
    Window::Terminate();

    return 0;
}