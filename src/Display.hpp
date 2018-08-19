#pragma once

#include <cstddef>
#include <string>
#include <SDL2/SDL.h>

namespace OpenGLTutorial {

class Display final
{
public: // methods
    explicit Display(
        std::size_t width,
        std::size_t height,
        const std::string &title);

    explicit Display(const Display &) = delete;
    Display &operator=(const Display &) = delete;

    ~Display();

    void clear(float r, float g, float b, float a);
    void update();

    bool isClosed() const;

private: // fields
    SDL_Window *m_window;
    SDL_GLContext m_glcontext;
    bool m_closed;
};

} // namespace OpenGLTutorial
