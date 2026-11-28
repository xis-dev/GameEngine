#include "../../../../include/AGP_Engine/Core/ECS/Components/Transform.h"

void AGPEngine::Transform::setPosition(const glm::vec3 &pos) {
    m_position = pos;
}

void AGPEngine::Transform::setScale(const glm::vec3 &s) {
    m_scale = s;
}

void AGPEngine::Transform::setRotation(const glm::vec3 &rot) {
    m_rotation = rot;
}

void AGPEngine::Transform::setRotationDegrees(const glm::vec3 &rotDeg) {
    m_rotation = glm::radians(rotDeg);
}

void AGPEngine::Transform::move(const glm::vec3& translation) {
    m_position += translation;
}

glm::mat4 AGPEngine::Transform::getTransform() const {

    glm::mat4 test = glm::mat4{1.0f};
    glm::mat4 out = glm::scale(test, m_scale);
    out = glm::toMat4(glm::quat(m_rotation)) * out;
    out = glm::translate(out, m_position);
    return out;
}
