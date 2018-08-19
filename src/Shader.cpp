#include "Shader.hpp"
#include <sstream>
#include <stdexcept>
#include "Utility.hpp"

namespace {

void checkShaderError(
    GLuint shader,
    GLuint flag,
    bool is_program,
    const std::string &message)
{
    static constexpr std::size_t c_message_size = 1024;

    GLint success;

    if (is_program)
    {
        glGetProgramiv(shader, flag, &success);
    }
    else
    {
        glGetShaderiv(shader, flag, &success);
    }

    if (GL_FALSE == success)
    {
        GLsizei message_size;
        GLchar error_message[c_message_size] = {0};

        if (is_program)
        {
            glGetProgramInfoLog(
                shader, sizeof(error_message), &message_size, error_message);
        }
        else
        {
            glGetShaderInfoLog(
                shader, sizeof(error_message), &message_size, error_message);
        }

        std::ostringstream ss;

        ss << message << std::endl;

        if (message_size > 0)
        {
            ss << error_message;
        }

        throw std::runtime_error(ss.str());
    }
}

GLuint createShader(const std::string &text, GLenum type)
{
    GLuint shader = glCreateShader(type);

    if (0 == shader)
    {
        throw std::runtime_error("shader creation failed");
    }

    const GLchar *shader_sources[1];
    GLint shader_sizes[1];

    shader_sources[0] = text.c_str();
    shader_sizes[0] = static_cast<GLint>(text.size());

    glShaderSource(shader, 1, shader_sources, shader_sizes);
    glCompileShader(shader);

    // checkShaderError(
    //     shader, GL_COMPILE_STATUS, false, "shader compilation failed");

    return shader;
}

} // namespace

namespace OpenGLTutorial {

Shader::Shader(
    const std::string &vertex_shader_filename,
    const std::string &fragment_shader_filename)
{
    m_program = glCreateProgram();

    m_shaders[0] =
        createShader(loadFile(vertex_shader_filename), GL_VERTEX_SHADER);
    m_shaders[1] =
        createShader(loadFile(fragment_shader_filename), GL_FRAGMENT_SHADER);

    for (std::size_t i = 0; i < NUM_SHADERS; i++)
    {
        glAttachShader(m_program, m_shaders[i]);
    }

    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "tex_coord");

    glLinkProgram(m_program);
    checkShaderError(m_program, GL_LINK_STATUS, true, "shader linking failed");

    glValidateProgram(m_program);
    checkShaderError(m_program, GL_VALIDATE_STATUS, true, "invalid shader");
}

Shader::~Shader()
{
    for (std::size_t i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

void Shader::bind()
{
    glUseProgram(m_program);
}

} // namespace OpenGLTutorial
