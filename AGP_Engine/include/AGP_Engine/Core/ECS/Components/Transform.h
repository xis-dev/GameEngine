#pragma once

#include "Component.h"
#include "glm/vec3.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

#include <iostream>

namespace AGPEngine {

    struct Transform: public Component{

    private:
        glm::vec3 m_position{};
        glm::vec3 m_scale{1.0f};
        // Rotation stored in euler angles(radians)
        glm::vec3 m_rotation{};

    public:
        Transform() = default;
        const glm::vec3& getPosition() const {return m_position;}
        const glm::vec3& getScale() const {return m_scale;}
        const glm::vec3& getRotation() const {return m_rotation;}

        void setPosition(const glm::vec3& pos);
        void setScale(const glm::vec3& s);

        // Set rotation in radians
        void setRotation(const glm::vec3& rot);
        void setRotationDegrees(const glm::vec3 &rotDeg);
        void move(const glm::vec3& translation);

        [[nodiscard]] glm::mat4 getTransform() const;

    };
}
