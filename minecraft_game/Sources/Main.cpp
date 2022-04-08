#include "Window/Window.hpp"
#include "Window/Events.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void)
{
    Window::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, "Voxel Engine");
    Events::Initialize();

    // loop until the user closes the window
    glClearColor(0.5f, 0.5f, 0.5f, 1);

    while (!Window::ShouldClose())
    {
        // poll for and process events
        Events::PollEvents();

        if (Events::justPressed(GLFW_KEY_ESCAPE))
        {
            Window::SetShouldClose(true);
        }
        if (Events::justClicked(GLFW_MOUSE_BUTTON_1))
        {
            glClearColor(1, 0, 0, 1);
        }

    	// render image
        glClear(GL_COLOR_BUFFER_BIT);

        // swap front and back buffers
        Window::SwapBuffers();

    }

    Window::Terminate();

    return 0;
}