#include "Mesh.hpp"
#include "obj_loader.hpp"

namespace OpenGLTutorial {

Mesh::Mesh(
    const std::vector<Vertex> &vertices,
    const std::vector<uint32_t> &indices)
{
    IndexedModel model;

    for (const auto &vertex : vertices)
    {
        model.positions.push_back(vertex.pos);
        model.texCoords.push_back(vertex.tex_coord);
        model.normals.push_back(vertex.normal);
    }

    for (const auto &index : indices)
    {
        model.indices.push_back(index);
    }

    initMesh(model);
}

Mesh::Mesh(const std::string &filename)
{
    initMesh(OBJModel(filename).toIndexedModel());
}

void Mesh::draw()
{
    glBindVertexArray(m_vertex_array_object);
    glDrawElements(GL_TRIANGLES, m_draw_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::initMesh(const IndexedModel &model)
{
    m_draw_count = static_cast<GLsizei>(model.indices.size());

    glGenVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    glGenBuffers(NUM_BUFFERS, m_vertex_array_buffers);

    glBindBuffer(
        GL_ARRAY_BUFFER, m_vertex_array_buffers[POSITION_VERTEX_BUFFER]);
    glBufferData(
        GL_ARRAY_BUFFER,
        model.positions.size() * sizeof(model.positions[0]),
        &model.positions[0],
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(
        GL_ARRAY_BUFFER, m_vertex_array_buffers[TEX_COORD_VERTEX_BUFFER]);
    glBufferData(
        GL_ARRAY_BUFFER,
        model.texCoords.size() * sizeof(model.texCoords[0]),
        &model.texCoords[0],
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_array_buffers[NORMAL_VERTEX_BUFFER]);
    glBufferData(
        GL_ARRAY_BUFFER,
        model.normals.size() * sizeof(model.normals[0]),
        &model.normals[0],
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER, m_vertex_array_buffers[INDEX_VERTEX_BUFFER]);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        model.indices.size() * sizeof(model.indices[0]),
        &model.indices[0],
        GL_STATIC_DRAW);

    glBindVertexArray(0);
}

} // namespace OpenGLTutorial
