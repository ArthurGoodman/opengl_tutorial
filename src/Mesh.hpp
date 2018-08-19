#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace OpenGLTutorial {

class Vertex final
{
public: // methods
    explicit Vertex(const glm::vec3 &pos);

private: // fields
    glm::vec3 m_pos;
};

class Mesh final
{
public: // methods
    explicit Mesh(const std::vector<Vertex> &vertices);

    explicit Mesh(const Mesh &) = delete;
    Mesh &operator=(const Mesh &) = delete;

    void draw();

private: // fields
    enum
    {
        POSITION_VERTEX_BUFFER,

        NUM_BUFFERS,
    };

    GLuint m_vertex_array_object;
    GLuint m_vertex_array_buffers[NUM_BUFFERS];
    GLsizei m_draw_count;
};

} // namespace OpenGLTutorial
