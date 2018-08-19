#include "Display.hpp"
#include <iostream>
#include <stdexcept>
#include <GL/glew.h>

namespace OpenGLTutorial {

Display::Display(
    std::size_t width,
    std::size_t height,
    const std::string &title)
    : m_closed{false}
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        throw std::runtime_error("SDL failed to initialize");
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        static_cast<int>(width),
        static_cast<int>(height),
        SDL_WINDOW_OPENGL);

    m_glcontext = SDL_GL_CreateContext(m_window);

    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("GLEW failed to initialize");
    }

    glEnable(GL_DEPTH_TEST);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
}

Display::~Display()
{
    SDL_GL_DeleteContext(m_glcontext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::update()
{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (SDL_QUIT == e.type)
        {
            m_closed = true;
        }
        else if (SDL_KEYDOWN == e.type)
        {
            if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                m_closed = true;
            }
        }
    }
}

bool Display::isClosed() const
{
    return m_closed;
}

} // namespace OpenGLTutorial
