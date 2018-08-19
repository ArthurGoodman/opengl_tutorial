#include "obj_loader.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

namespace {

using namespace OpenGLTutorial;

bool compareOBJIndexPtr(const OBJIndex *a, const OBJIndex *b)
{
    return a->vertexIndex < b->vertexIndex;
}

uint32_t findNextChar(
    uint32_t start,
    const char *str,
    std::size_t length,
    char token)
{
    uint32_t result = start;
    while (result < length)
    {
        result++;
        if (str[result] == token)
            break;
    }

    return result;
}

uint32_t parseOBJIndexValue(
    const std::string &token,
    uint32_t start,
    uint32_t end)
{
    return static_cast<uint32_t>(
        std::stoi(token.substr(start, end - start)) - 1);
}

float parseOBJFloatValue(const std::string &token, uint32_t start, uint32_t end)
{
    return std::stof(token.substr(start, end - start));
}

std::vector<std::string> splitString(const std::string &s, char delim)
{
    std::vector<std::string> elems;

    const char *cstr = s.c_str();
    std::size_t strLength = s.length();
    uint32_t start = 0;
    uint32_t end = 0;

    while (end <= strLength)
    {
        while (end <= strLength)
        {
            if (cstr[end] == delim)
                break;
            end++;
        }

        elems.push_back(s.substr(start, end - start));
        start = end + 1;
        end = start;
    }

    return elems;
}

} // anonymous namespace

namespace OpenGLTutorial {

OBJModel::OBJModel(const std::string &fileName)
{
    hasUVs = false;
    hasNormals = false;
    std::ifstream file;
    file.open(fileName.c_str());

    std::string line;
    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);

            std::size_t lineLength = line.length();

            if (lineLength < 2)
                continue;

            const char *lineCStr = line.c_str();

            switch (lineCStr[0])
            {
            case 'v':
                if (lineCStr[1] == 't')
                    this->uvs.push_back(parseOBJVec2(line));
                else if (lineCStr[1] == 'n')
                    this->normals.push_back(parseOBJVec3(line));
                else if (lineCStr[1] == ' ' || lineCStr[1] == '\t')
                    this->vertices.push_back(parseOBJVec3(line));
                break;
            case 'f':
                createOBJFace(line);
                break;
            default:
                break;
            };
        }
    }
    else
    {
        std::cerr << "Unable to load mesh: " << fileName << std::endl;
    }
}

void IndexedModel::calcNormals()
{
    for (uint32_t i = 0; i < indices.size(); i += 3)
    {
        uint32_t i0 = indices[i];
        uint32_t i1 = indices[i + 1];
        uint32_t i2 = indices[i + 2];

        glm::vec3 v1 = positions[i1] - positions[i0];
        glm::vec3 v2 = positions[i2] - positions[i0];

        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

        normals[i0] += normal;
        normals[i1] += normal;
        normals[i2] += normal;
    }

    for (uint32_t i = 0; i < positions.size(); i++)
        normals[i] = glm::normalize(normals[i]);
}

IndexedModel OBJModel::toIndexedModel()
{
    IndexedModel result;
    IndexedModel normalModel;

    std::size_t numIndices = OBJIndices.size();

    std::vector<OBJIndex *> indexLookup;

    for (uint32_t i = 0; i < numIndices; i++)
        indexLookup.push_back(&OBJIndices[i]);

    std::sort(indexLookup.begin(), indexLookup.end(), compareOBJIndexPtr);

    std::map<OBJIndex, uint32_t> normalModelIndexMap;
    std::map<uint32_t, uint32_t> indexMap;

    for (uint32_t i = 0; i < numIndices; i++)
    {
        OBJIndex *currentIndex = &OBJIndices[i];

        glm::vec3 currentPosition = vertices[currentIndex->vertexIndex];
        glm::vec2 currentTexCoord;
        glm::vec3 currentNormal;

        if (hasUVs)
            currentTexCoord = uvs[currentIndex->uvIndex];
        else
            currentTexCoord = glm::vec2(0, 0);

        if (hasNormals)
            currentNormal = normals[currentIndex->normalIndex];
        else
            currentNormal = glm::vec3(0, 0, 0);

        uint32_t normalModelIndex;
        uint32_t resultModelIndex;

        // Create model to properly generate normals on
        std::map<OBJIndex, uint32_t>::iterator it =
            normalModelIndexMap.find(*currentIndex);
        if (it == normalModelIndexMap.end())
        {
            normalModelIndex =
                static_cast<uint32_t>(normalModel.positions.size());

            normalModelIndexMap.insert(
                std::pair<OBJIndex, uint32_t>(*currentIndex, normalModelIndex));
            normalModel.positions.push_back(currentPosition);
            normalModel.texCoords.push_back(currentTexCoord);
            normalModel.normals.push_back(currentNormal);
        }
        else
            normalModelIndex = it->second;

        // Create model which properly separates texture coordinates
        uint32_t previousVertexLocation =
            findLastVertexIndex(indexLookup, currentIndex, result);

        if (previousVertexLocation == (uint32_t)-1)
        {
            resultModelIndex = static_cast<uint32_t>(result.positions.size());

            result.positions.push_back(currentPosition);
            result.texCoords.push_back(currentTexCoord);
            result.normals.push_back(currentNormal);
        }
        else
            resultModelIndex = previousVertexLocation;

        normalModel.indices.push_back(normalModelIndex);
        result.indices.push_back(resultModelIndex);
        indexMap.insert(
            std::pair<uint32_t, uint32_t>(resultModelIndex, normalModelIndex));
    }

    if (!hasNormals)
    {
        normalModel.calcNormals();

        for (uint32_t i = 0; i < result.positions.size(); i++)
            result.normals[i] = normalModel.normals[indexMap[i]];
    }

    return result;
};

uint32_t OBJModel::findLastVertexIndex(
    const std::vector<OBJIndex *> &indexLookup,
    const OBJIndex *currentIndex,
    const IndexedModel &result)
{
    std::size_t start = 0;
    std::size_t end = indexLookup.size();
    std::size_t current = (end - start) / 2 + start;
    std::size_t previous = start;

    while (current != previous)
    {
        OBJIndex *testIndex = indexLookup[current];

        if (testIndex->vertexIndex == currentIndex->vertexIndex)
        {
            std::size_t countStart = current;

            for (uint32_t i = 0; i < current; i++)
            {
                OBJIndex *possibleIndex = indexLookup[current - i];

                if (possibleIndex == currentIndex)
                    continue;

                if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
                    break;

                countStart--;
            }

            for (std::size_t i = countStart;
                 i < indexLookup.size() - countStart;
                 i++)
            {
                OBJIndex *possibleIndex = indexLookup[current + i];

                if (possibleIndex == currentIndex)
                    continue;

                if (possibleIndex->vertexIndex != currentIndex->vertexIndex)
                    break;
                else if (
                    (!hasUVs ||
                     possibleIndex->uvIndex == currentIndex->uvIndex) &&
                    (!hasNormals ||
                     possibleIndex->normalIndex == currentIndex->normalIndex))
                {
                    glm::vec3 currentPosition =
                        vertices[currentIndex->vertexIndex];
                    glm::vec2 currentTexCoord;
                    glm::vec3 currentNormal;

                    if (hasUVs)
                        currentTexCoord = uvs[currentIndex->uvIndex];
                    else
                        currentTexCoord = glm::vec2(0, 0);

                    if (hasNormals)
                        currentNormal = normals[currentIndex->normalIndex];
                    else
                        currentNormal = glm::vec3(0, 0, 0);

                    for (uint32_t j = 0; j < result.positions.size(); j++)
                    {
                        if (currentPosition == result.positions[j] &&
                            ((!hasUVs ||
                              currentTexCoord == result.texCoords[j]) &&
                             (!hasNormals ||
                              currentNormal == result.normals[j])))
                        {
                            return j;
                        }
                    }
                }
            }

            return -1u;
        }
        else
        {
            if (testIndex->vertexIndex < currentIndex->vertexIndex)
                start = current;
            else
                end = current;
        }

        previous = current;
        current = (end - start) / 2 + start;
    }

    return -1u;
}

void OBJModel::createOBJFace(const std::string &line)
{
    std::vector<std::string> tokens = splitString(line, ' ');

    this->OBJIndices.push_back(
        parseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
    this->OBJIndices.push_back(
        parseOBJIndex(tokens[2], &this->hasUVs, &this->hasNormals));
    this->OBJIndices.push_back(
        parseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));

    if ((int)tokens.size() > 4)
    {
        this->OBJIndices.push_back(
            parseOBJIndex(tokens[1], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(
            parseOBJIndex(tokens[3], &this->hasUVs, &this->hasNormals));
        this->OBJIndices.push_back(
            parseOBJIndex(tokens[4], &this->hasUVs, &this->hasNormals));
    }
}

OBJIndex OBJModel::parseOBJIndex(
    const std::string &token,
    bool *hasUVs,
    bool *hasNormals)
{
    std::size_t tokenLength = token.length();
    const char *tokenString = token.c_str();

    uint32_t vertIndexStart = 0;
    uint32_t vertIndexEnd =
        findNextChar(vertIndexStart, tokenString, tokenLength, '/');

    OBJIndex result;
    result.vertexIndex =
        parseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    result.uvIndex = 0;
    result.normalIndex = 0;

    if (vertIndexEnd >= tokenLength)
        return result;

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = findNextChar(vertIndexStart, tokenString, tokenLength, '/');

    result.uvIndex = parseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    *hasUVs = true;

    if (vertIndexEnd >= tokenLength)
        return result;

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = findNextChar(vertIndexStart, tokenString, tokenLength, '/');

    result.normalIndex =
        parseOBJIndexValue(token, vertIndexStart, vertIndexEnd);
    *hasNormals = true;

    return result;
}

glm::vec3 OBJModel::parseOBJVec3(const std::string &line)
{
    std::size_t tokenLength = line.length();
    const char *tokenString = line.c_str();

    uint32_t vertIndexStart = 2;

    while (vertIndexStart < tokenLength)
    {
        if (tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }

    uint32_t vertIndexEnd =
        findNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float x = parseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = findNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float y = parseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = findNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float z = parseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    return glm::vec3(x, y, z);

    // glm::vec3(atof(tokens[1].c_str()), atof(tokens[2].c_str()),
    // atof(tokens[3].c_str()))
}

glm::vec2 OBJModel::parseOBJVec2(const std::string &line)
{
    std::size_t tokenLength = line.size();
    const char *tokenString = line.c_str();

    uint32_t vertIndexStart = 3;

    while (vertIndexStart < tokenLength)
    {
        if (tokenString[vertIndexStart] != ' ')
            break;
        vertIndexStart++;
    }

    uint32_t vertIndexEnd =
        findNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float x = parseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    vertIndexStart = vertIndexEnd + 1;
    vertIndexEnd = findNextChar(vertIndexStart, tokenString, tokenLength, ' ');

    float y = parseOBJFloatValue(line, vertIndexStart, vertIndexEnd);

    return glm::vec2(x, y);
}

} // namespace OpenGLTutorial
