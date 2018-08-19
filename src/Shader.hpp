#pragma once

#include <cstddef>
#include <string>
#include <GL/glew.h>

namespace OpenGLTutorial {

class Shader final
{
public: // methods
    explicit Shader(
        const std::string &vertex_shader_filename,
        const std::string &fragment_shader_filename);

    explicit Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

    ~Shader();

    void bind();

private: // fields
    static constexpr std::size_t NUM_SHADERS = 2;

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};

} // namespace OpenGLTutorial
