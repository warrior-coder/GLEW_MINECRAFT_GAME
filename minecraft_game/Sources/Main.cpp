#include <iostream>

#include "Window/Window.hpp"
#include "Window/Events.hpp"
#include "Window/Camera.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Mesh.hpp"

#include <GLM/gtc/matrix_transform.hpp>

constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 720;

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
    const GLint attributes[] = {
        3, 2, NULL
    };
    Mesh* mesh = new Mesh(vertexCoordinates, 6, attributes);

    // очистка изображения
    glClearColor(0.5f, 0.5f, 0.5f, 1);

    // включение смешивания для корректной прозрачности
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // камера
    Camera* camera = new Camera(
        glm::vec3(0, 0, 1),
        glm::radians(70.0f)
    );
    glm::mat4 modelView(1.0f); // матрица трансформации модели

    // время
    double lastTime = glfwGetTime();
    double deltaTime;
    double currentTime;
    float speed = 5.0f;
    float cameraRotateX = 0.0f;
    float cameraRotateY = 0.0f;

    // основной цикл программы
    while (!Window::ShouldClose())
    {
        // вычисляем разницу времени для стабильного FPS
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;


        // обработка событий клавиш
        if (Events::KeyJustPressed(GLFW_KEY_ESCAPE))
        {
            Window::SetShouldClose(true);
        }
        if (Events::MouseJustClicked(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(0, 0, 0, 1);
        }
        if (Events::KeyJustPressed(GLFW_KEY_TAB))
        {
            Events::ToggleCursor();
        }
    	// перемещение WASD
        if (Events::KeyPressed(GLFW_KEY_W))
        {
            camera->position += camera->front * (float)deltaTime * speed;
        }
    	if (Events::KeyPressed(GLFW_KEY_S))
        {
            camera->position -= camera->front * (float)deltaTime * speed;
        }
        if (Events::KeyPressed(GLFW_KEY_D))
        {
            camera->position += camera->right * (float)deltaTime * speed;
        }
    	if (Events::KeyPressed(GLFW_KEY_A))
        {
            camera->position -= camera->right * (float)deltaTime * speed;
        }
        // поворот камеры (при заблокированном курсоре)
        if (Events::cursorLocked)
        {
        	cameraRotateX += -(float)Events::cursorDeltaX / (float)Window::width;
	        cameraRotateY += -(float)Events::cursorDeltaY / (float)Window::height;

	        if (cameraRotateY < -glm::radians(89.0f))
	        {
	            cameraRotateY = -glm::radians(89.0f);
	        }
        	if (cameraRotateY > glm::radians(89.0f))
	        {
	            cameraRotateY = glm::radians(89.0f);
	        }

    		camera->rotation = glm::mat4(1.0f);
    		camera->FirstPersonViewRotate(cameraRotateY, cameraRotateX, 0.0f);
        }
       

        
        glClear(GL_COLOR_BUFFER_BIT); // очистка изображения

    	// отрисовка 
        shader->Use();
        shader->UniformMatrix("model_view", modelView);
        shader->UniformMatrix("projection_view", camera->GetProjectionMatrix() * camera->GetViewMatrix());
        texture->Bind();
        mesh->Draw(GL_TRIANGLES);
		
        
        Window::SwapBuffers(); // обмен переднего и заднего буферов

       
        Events::PollEvents();  // запрос событий
    }

    // освобождение памяти
    delete shader;
    delete texture;
    delete camera;
    delete mesh;
    Window::Terminate();

    return 0;
}