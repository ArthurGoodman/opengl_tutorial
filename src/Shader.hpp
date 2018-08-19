#pragma once

#include <cstddef>
#include <string>
#include <GL/glew.h>
#include "Camera.hpp"
#include "Transform.hpp"

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

    void update(const Transform &transform, const Camera &camera);

private: // fields
    static constexpr std::size_t NUM_SHADERS = 2;

    enum
    {
        MVP_UNIFORM,

        NUM_UNIFORMS,
    };

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLint m_uniforms[NUM_UNIFORMS];
};

} // namespace OpenGLTutorial
