#include <exception>
#include <iostream>
#include <GL/glew.h>
#include "Display.hpp"
#include "Shader.hpp"

int main(int /*argc*/, const char ** /*argv*/) try
{
    using namespace OpenGLTutorial;

    Display display(800, 600, "My Window");

    Shader shader("./res/shader.vert", "./res/shader.frag");

    while (!display.isClosed())
    {
        display.clear(0.11f, 0.12f, 0.13f, 1.0f);
        shader.bind();
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
