#include <exception>
#include <iostream>
#include <GL/glew.h>
#include "Display.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

int main(int /*argc*/, const char ** /*argv*/) try
{
    using namespace OpenGLTutorial;

    Display display(800, 600, "My Window");

    Shader shader("./res/shader.vert", "./res/shader.frag");

    std::vector<Vertex> vertices{
        Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 0.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 1.0f)},
    };

    Mesh mesh(vertices);

    Texture texture("./res/texture.jpg");

    while (!display.isClosed())
    {
        display.clear(0.11f, 0.12f, 0.13f, 1.0f);

        shader.bind();
        texture.bind(0);
        mesh.draw();

        display.update();
    }

    return 0;
}
catch (const std::exception &e)
{
    std::cerr << "error: " << e.what() << std::endl;
}
catch (...)
{
    std::cerr << "unknown error occurred" << std::endl;
}
