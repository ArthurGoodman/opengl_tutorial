#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace OpenGLTutorial {

class Vertex final
{
public: // methods
    explicit Vertex(const glm::vec3 &pos, const glm::vec2 &tex_coord);

    glm::vec3 getPos() const;
    glm::vec2 getTexCoord() const;

private: // fields
    glm::vec3 m_pos;
    glm::vec2 m_tex_coord;
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
