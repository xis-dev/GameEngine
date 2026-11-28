//
// Created by Joni on 28/11/2026.
//

#include "AGP_Engine/Graphics/Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

namespace AGPEngine {

    // Depth range for the projection. Generous so entities can be layered along Z if needed.
    static constexpr float NearPlane = -100.0f;
    static constexpr float FarPlane = 100.0f;

    void Camera2D::setViewport(int pixelWidth, int pixelHeight) {
        if (pixelWidth <= 0 || pixelHeight <= 0) return;
        m_pixelWidth = pixelWidth;
        m_pixelHeight = pixelHeight;
        m_aspect = static_cast<float>(pixelWidth) / static_cast<float>(pixelHeight);
    }

    void Camera2D::setZoom(float zoom) {
        if (zoom > 0.0f) m_zoom = zoom;
    }

    void Camera2D::setViewHeight(float worldUnits) {
        if (worldUnits > 0.0f) m_viewHeight = worldUnits;
    }

    glm::vec2 Camera2D::halfExtents() const {
        const float halfHeight = m_viewHeight / (2.0f * m_zoom);
        return {halfHeight * m_aspect, halfHeight};
    }

    glm::mat4 Camera2D::getViewProjection() const {
        const glm::vec2 half = halfExtents();
        const glm::mat4 projection = glm::ortho(-half.x, half.x, -half.y, half.y, NearPlane, FarPlane);
        const glm::mat4 view = glm::translate(glm::mat4{1.0f}, glm::vec3{-m_position, 0.0f});
        return projection * view;
    }

    glm::vec2 Camera2D::screenToWorld(const glm::vec2& pixel) const {
        // Pixels (origin top-left, y down) -> NDC (origin centre, y up) -> world
        const glm::vec2 ndc{
            2.0f * pixel.x / static_cast<float>(m_pixelWidth) - 1.0f,
            1.0f - 2.0f * pixel.y / static_cast<float>(m_pixelHeight)
        };
        return m_position + ndc * halfExtents();
    }
}