#pragma once

#include <cstdint>
#include <string>
#include <GL/glew.h>

namespace OpenGLTutorial {

class Texture final
{
public: // methods
    explicit Texture(const std::string &filename);
    ~Texture();

    void bind(std::uint32_t unit);

private: // fields
    GLuint m_texture;
};

} // namespace OpenGLTutorial
