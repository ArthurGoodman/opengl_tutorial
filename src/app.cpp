#include <GL/glew.h>
#include "Display.hpp"

int main(int /*argc*/, const char ** /*argv*/)
{
    using namespace OpenGLTutorial;

    Display display(800, 600, "My Window");

    while (!display.isClosed())
    {
        display.clear(0.11f, 0.12f, 0.13f, 1.0f);
        display.update();
    }

    return 0;
}
