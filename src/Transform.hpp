#pragma once

#include <glm/glm.hpp>

namespace OpenGLTutorial {

class Transform final
{
public: // methods
    explicit Transform(
        const glm::vec3 &position = glm::vec3(),
        const glm::vec3 &rotation = glm::vec3(),
        const glm::vec3 &scale = glm::vec3(1, 1, 1));

    glm::vec3 &getPosition();
    glm::vec3 &getRotation();
    glm::vec3 &getScale();

    void setPosition(const glm::vec3 &position);
    void setRotation(const glm::vec3 &rotation);
    void setScale(const glm::vec3 &scale);

    glm::mat4 getModel() const;

private: // fields
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};

} // namespace OpenGLTutorial
