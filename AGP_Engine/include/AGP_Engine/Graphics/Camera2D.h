//
// Created by Joni on 28/11/2026.
//

#pragma once

#include <glm/glm.hpp>

namespace AGPEngine {

    // Orthographic 2D camera.
    //
    // The camera shows `viewHeight / zoom` world units vertically; the horizontal extent follows the
    // viewport's aspect ratio, so sprites are never stretched when the window is resized.
    // World space: +X right, +Y up, one unit = one Transform scale unit (a scale-1 sprite is 1x1).
    class Camera2D {

    public:
        explicit Camera2D(float viewHeight = 10.0f) : m_viewHeight(viewHeight) {}

        // Viewport size in pixels, used for the aspect ratio. Ignores non-positive sizes (minimised window).
        void setViewport(int pixelWidth, int pixelHeight);

        void setPosition(const glm::vec2& pos) { m_position = pos; }
        void move(const glm::vec2& delta) { m_position += delta; }
        [[nodiscard]] const glm::vec2& getPosition() const { return m_position; }

        // Zoom multiplies the apparent size of things: 2 shows half as much of the world.
        void setZoom(float zoom);
        [[nodiscard]] float getZoom() const { return m_zoom; }

        // How many world units are visible vertically at zoom 1.
        void setViewHeight(float worldUnits);
        [[nodiscard]] float getViewHeight() const { return m_viewHeight; }

        [[nodiscard]] float getAspect() const { return m_aspect; }

        // Projection * View, ready to upload as a uniform.
        [[nodiscard]] glm::mat4 getViewProjection() const;

        // Convert a position in window pixels (origin top-left, as SDL reports it) to world coordinates.
        [[nodiscard]] glm::vec2 screenToWorld(const glm::vec2& pixel) const;

    private:
        [[nodiscard]] glm::vec2 halfExtents() const;

        glm::vec2 m_position{0.0f};
        float m_zoom{1.0f};
        float m_viewHeight{10.0f};
        float m_aspect{1.0f};
        int m_pixelWidth{1};
        int m_pixelHeight{1};
    };
}