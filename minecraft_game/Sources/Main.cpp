#include <iostream>

#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Window/Camera.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"

#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 720;

int main()
{
    Window::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Voxel Engine");
    Events::Initialize();

    // �������� ��������
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

    // �������� ������ ��������� ������
    const GLfloat vertexCoordinates[] = {
    //   X   Y   Z   U   V
        -1, -1,  0,  0,  0,
         1, -1,  0,  1,  0,
    	-1,  1,  0,  0,  1,

         1, -1,  0,  1,  0,
         1,  1,  0,  1,  1,
    	-1,  1,  0,  0,  1
    }; // ������ ��������� ������
    GLuint vertexCoordinatesBufferId;

	glGenBuffers(1, &vertexCoordinatesBufferId); // ���������� 1 ����� ��� VBO (Vertex Buffer Object) �� ����������
    glBindBuffer(GL_ARRAY_BUFFER, vertexCoordinatesBufferId); // ��������� vertexCoordinatesBufferId � �������
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoordinates), vertexCoordinates, GL_STATIC_DRAW); // �������� ������ vertexCoordinates �� ����������� ������ � ����� �� ����������

    // ��������� ��������� �������� ��� VAO
    GLuint vertexArrayId;

    glGenVertexArrays(1, &vertexArrayId); // ���������� 1 ����� ��� VAO (Vertex Array Object) �� ����������
	glBindVertexArray(vertexArrayId); // ����������� VAO
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	    glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	    glEnableVertexAttribArray(1);
    glBindVertexArray(0u); // ���������� VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0u); // ������������ �� ������

    // ������� �����������
    glClearColor(0.5f, 0.5f, 0.5f, 1);

    // ��������� ���������� ��� ���������� ������������
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ������
    Camera* camera = new Camera(glm::vec3(0, 0, 1), 0.5f);

    glm::mat4 model(1.0f); // ������� ������������� �������
    model = glm::translate(model, glm::vec3(0.5f, 0, 0)); // ������� ����������������� �� ������ �������, � ���������� �����

    // �����
    double lastTime = glfwGetTime();
    double deltaTime = 0.0;
    double currentTime;
    float speed = 5.0f;

    // �������� ���� ���������
    while (!Window::ShouldClose())
    {
        // ��������� ������� ������� ��� ����������� FPS
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // ��������� �������
        if (Events::KeyJustPressed(GLFW_KEY_ESCAPE))
        {
            Window::SetShouldClose(true);
        }
        if (Events::MouseJustClicked(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(0, 0, 0, 1);
        }
        if (Events::KeyPressed(GLFW_KEY_W))
        {
            camera->position += camera->front * static_cast<float>(deltaTime) * speed;
        }
    	if (Events::KeyPressed(GLFW_KEY_S))
        {
            camera->position -= camera->front * static_cast<float>(deltaTime) * speed;
        }
        if (Events::KeyPressed(GLFW_KEY_D))
        {
            camera->position += camera->right * static_cast<float>(deltaTime) * speed;
        }
    	if (Events::KeyPressed(GLFW_KEY_A))
        {
            camera->position -= camera->right * static_cast<float>(deltaTime) * speed;
        }

        // ������� �����������
        glClear(GL_COLOR_BUFFER_BIT);

    	// ��������� VAO
        shader->Use();
        shader->UniformMatrix("model_view", model);
        shader->UniformMatrix(
            "projection_view",
            camera->GetProjectionMatrix() * camera->GetViewMatrix()
        );
        texture->Bind();
		
        glBindVertexArray(vertexArrayId);
			glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0u);

        // ����� ��������� � ������� �������
        Window::SwapBuffers();

        // ������ �������
        Events::PollEvents();
    }

    // ������������ ������
    delete shader;
    delete texture;
    glDeleteBuffers(1, &vertexCoordinatesBufferId); // �������� ���������� ������
    glDeleteVertexArrays(1, &vertexArrayId); // �������� ���������� �������
    Window::Terminate();

    return 0;
}