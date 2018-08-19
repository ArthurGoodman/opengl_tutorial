#include "Mesh.hpp"

namespace OpenGLTutorial {

Vertex::Vertex(const glm::vec3 &pos)
    : m_pos{pos}
{
}

Mesh::Mesh(const std::vector<Vertex> &vertices)
{
    m_draw_count = static_cast<GLsizei>(vertices.size());

    glGenVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    glGenBuffers(NUM_BUFFERS, m_vertex_array_buffers);
    glBindBuffer(
        GL_ARRAY_BUFFER, m_vertex_array_buffers[POSITION_VERTEX_BUFFER]);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(vertices[0]),
        &vertices[0],
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

void Mesh::draw()
{
    glBindVertexArray(m_vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, m_draw_count);
    glBindVertexArray(0);
}

} // namespace OpenGLTutorial
