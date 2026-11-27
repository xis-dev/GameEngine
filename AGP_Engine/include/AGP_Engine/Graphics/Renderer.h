#pragma once

#include "AGP_Engine/Core/Window.h"
#include "AGP_Engine/Resources/Shader.h"
#include "AGP_Engine/Core/Level.h"
#include "Primitives/QuadMesh.h"

namespace AGPEngine {

    class Renderer {

    public:
        Renderer(Window* win, int vpWidth, int vpHeight);
        ~Renderer() = default;
        
        static void Init();
        static void Shutdown();

        void render(const Level& level);
        void destroy();
        void changeContextWindow(Window* win);

    private:
        int m_viewportWidth{};
        int m_viewportHeight{};
        Window* m_renderWindow{nullptr};


        // Temporary variables
        std::unique_ptr<QuadMesh> m_spriteMesh {nullptr};
        Shader m_spriteShader{};
        // Cached so we dont constantly need to get location every frame
        uint32_t m_modelMatrixSSBOLocation{};
        // Cached so we can avoid rebuilding the ssbo every frame, only when its more or less
        GLBufferObject m_modelMatrixSSBO{};
        std::vector<glm::mat4> m_modelMatrices{};
    };
}
