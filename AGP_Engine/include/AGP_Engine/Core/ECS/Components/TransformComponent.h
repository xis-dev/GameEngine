#pragma once

#include "Component.h"
#include "glm/vec3.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

namespace AGPEngine {

    struct Transform: public Component{

    private:
        glm::vec3 m_position{};
        glm::vec3 scale{};
        // Rotation stored in euler angles(radians)
        glm::vec3 rotation{};

    public:
        Transform() = default;
        const glm::vec3& getPosition() const {return m_position;}
        const glm::vec3& getScale() const {return scale;}
        const glm::vec3& getRotation() const {return rotation;}

        void setPosition(glm::vec3 pos);

        [[nodiscard]] glm::mat4 getTransform() const {
            glm::mat4 test = glm::mat4{1.0f};
            glm::mat4 out = glm::scale(test, scale);
            out = glm::toMat4(glm::quat(rotation)) * out;
            out = glm::translate(out, m_position);
            return out;
        }
    };
}
