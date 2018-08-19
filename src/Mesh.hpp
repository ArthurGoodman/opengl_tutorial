#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace OpenGLTutorial {

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 tex_coord;
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
        TEX_COORD_VERTEX_BUFFER,

        NUM_BUFFERS,
    };

    GLuint m_vertex_array_object;
    GLuint m_vertex_array_buffers[NUM_BUFFERS];
    GLsizei m_draw_count;
};

} // namespace OpenGLTutorial
