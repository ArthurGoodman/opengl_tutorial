#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace OpenGLTutorial {

class Camera final
{
public: // methods
    explicit Camera(
        const glm::vec3 &pos,
        float fov,
        float aspect,
        float z_near,
        float z_far)
        : m_perspective{glm::perspective(fov, aspect, z_near, z_far)}
        , m_position{pos}
        , m_forward{glm::vec3(0, 0, 1)}
        , m_up{glm::vec3(0, 1, 0)}
    {
    }

    glm::mat4 getViewProjection() const
    {
        return m_perspective *
               glm::lookAt(m_position, m_position + m_forward, m_up);
    }

private: // fields
    glm::mat4 m_perspective;
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
};

} // namespace OpenGLTutorial
