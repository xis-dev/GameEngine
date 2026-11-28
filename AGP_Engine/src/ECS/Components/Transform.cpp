//
// Created by Joni on 28/11/2026.
//

#include "AGP_Engine/Core/ECS/Components/Transform.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 AGPEngine::Transform::getTransform() const {
    // Model matrix is Transform * Rotation * Scale: scale first, then rotate, then translate.

    const glm::mat4 translation = glm::translate(glm::mat4{1.0f}, m_position);
    const glm::mat4 rotation = glm::toMat4(glm::quat(m_rotation));
    const glm::mat4 scale = glm::scale(glm::mat4{1.0f}, m_scale);
    return translation * rotation * scale;
}