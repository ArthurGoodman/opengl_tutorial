#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace OpenGLTutorial {

class IndexedModel;

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 tex_coord;
    glm::vec3 normal;
};

class Mesh final
{
public: // methods
    explicit Mesh(
        const std::vector<Vertex> &vertices,
        const std::vector<uint32_t> &indices);

    explicit Mesh(const std::string &filename);

    explicit Mesh(const Mesh &) = delete;
    Mesh &operator=(const Mesh &) = delete;

    void draw();

private: // methods
    void initMesh(const IndexedModel &model);

private: // fields
    enum
    {
        POSITION_VERTEX_BUFFER,
        TEX_COORD_VERTEX_BUFFER,
        NORMAL_VERTEX_BUFFER,

        INDEX_VERTEX_BUFFER,

        NUM_BUFFERS,
    };

    GLuint m_vertex_array_object;
    GLuint m_vertex_array_buffers[NUM_BUFFERS];
    GLsizei m_draw_count;
};

} // namespace OpenGLTutorial
