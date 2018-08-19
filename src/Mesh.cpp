#include "Mesh.hpp"

namespace OpenGLTutorial {

Mesh::Mesh(const std::vector<Vertex> &vertices)
{
    m_draw_count = static_cast<GLsizei>(vertices.size());

    glGenVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> tex_coords;

    positions.reserve(vertices.size());
    tex_coords.reserve(vertices.size());

    for (const auto &vertex : vertices)
    {
        positions.push_back(vertex.pos);
        tex_coords.push_back(vertex.tex_coord);
    }

    glGenBuffers(NUM_BUFFERS, m_vertex_array_buffers);

    glBindBuffer(
        GL_ARRAY_BUFFER, m_vertex_array_buffers[POSITION_VERTEX_BUFFER]);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(positions[0]),
        &positions[0],
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(
        GL_ARRAY_BUFFER, m_vertex_array_buffers[TEX_COORD_VERTEX_BUFFER]);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(tex_coords[0]),
        &tex_coords[0],
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void Mesh::draw()
{
    glBindVertexArray(m_vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, m_draw_count);
    glBindVertexArray(0);
}

} // namespace OpenGLTutorial
