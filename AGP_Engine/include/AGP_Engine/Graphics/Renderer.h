#pragma once

#include "AGP_Engine/Core/Window.h"
#include "AGP_Engine/Resources/Shader.h"
#include "Primitives/QuadMesh.h"

namespace AGPEngine {

    class Renderer {

    public:
        Renderer(Window* win, int vpWidth, int vpHeight);
        ~Renderer() = default;
        
        static void Init();
        static void Shutdown();


        void update();
        void destroy();
        void changeContextWindow(Window* win);

    private:
        int m_viewportWidth{};
        int m_viewportHeight{};
        Window* m_renderWindow{nullptr};


        // Temporary variables
        std::unique_ptr<QuadMesh> m_spriteMesh {nullptr};
        Shader m_spriteShader{};
    };
}
