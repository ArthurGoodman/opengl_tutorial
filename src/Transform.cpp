#include "Transform.hpp"

#include <glm/gtx/transform.hpp>

namespace OpenGLTutorial {

Transform::Transform(
    const glm::vec3 &position,
    const glm::vec3 &rotation,
    const glm::vec3 &scale)
    : m_position{position}
    , m_rotation{rotation}
    , m_scale{scale}
{
}

glm::vec3 &Transform::getPosition()
{
    return m_position;
}

glm::vec3 &Transform::getRotation()
{
    return m_rotation;
}

glm::vec3 &Transform::getScale()
{
    return m_scale;
}

void Transform::setPosition(const glm::vec3 &position)
{
    m_position = position;
}

void Transform::setRotation(const glm::vec3 &rotation)
{
    m_rotation = rotation;
}

void Transform::setScale(const glm::vec3 &scale)
{
    m_scale = scale;
}

glm::mat4 Transform::getModel() const
{
    glm::mat4 translation_mat = glm::translate(m_position);

    glm::mat4 rotation_x_mat = glm::rotate(m_rotation.x, glm::vec3{1, 0, 0});
    glm::mat4 rotation_y_mat = glm::rotate(m_rotation.y, glm::vec3{0, 1, 0});
    glm::mat4 rotation_z_mat = glm::rotate(m_rotation.z, glm::vec3{0, 0, 1});

    glm::mat4 scale_mat = glm::scale(m_scale);

    return translation_mat * rotation_z_mat * rotation_y_mat * rotation_x_mat *
           scale_mat;
}

} // namespace OpenGLTutorial
