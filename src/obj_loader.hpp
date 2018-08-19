#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace OpenGLTutorial {

struct IndexedModel
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<uint32_t> indices;

    void calcNormals();
};

struct OBJIndex
{
    uint32_t vertexIndex;
    uint32_t uvIndex;
    uint32_t normalIndex;

    bool operator<(const OBJIndex &r) const
    {
        return vertexIndex < r.vertexIndex;
    }
};

struct OBJModel
{
    std::vector<OBJIndex> OBJIndices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    bool hasUVs;
    bool hasNormals;

    explicit OBJModel(const std::string &fileName);

    IndexedModel toIndexedModel();

private:
    uint32_t findLastVertexIndex(
        const std::vector<OBJIndex *> &indexLookup,
        const OBJIndex *currentIndex,
        const IndexedModel &result);

    void createOBJFace(const std::string &line);

    glm::vec2 parseOBJVec2(const std::string &line);
    glm::vec3 parseOBJVec3(const std::string &line);

    OBJIndex parseOBJIndex(
        const std::string &token,
        bool *hasUVs,
        bool *hasNormals);
};

} // namespace OpenGLTutorial
