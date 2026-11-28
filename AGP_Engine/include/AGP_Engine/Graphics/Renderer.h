#pragma once

#include "AGP_Engine/Core/Window.h"
#include "AGP_Engine/Resources/Shader.h"
#include "AGP_Engine/Core/Level.h"
#include "AGP_Engine/Graphics/Camera2D.h"
#include "Primitives/QuadMesh.h"

namespace AGPEngine {

    class Renderer {

    public:
        Renderer(Window* win, int vpWidth, int vpHeight);
        ~Renderer() = default;
        
        static void Init();
        static void Shutdown();

        //Fails if GL loading or shader creation fails.
        [[nodiscard]] bool isValid() const { return m_valid; }

        void render(const Level& level);
        void destroy();
        void changeContextWindow(Window* win);

        [[nodiscard]] Camera2D& getCamera() {return m_camera;};
        [[nodiscard]] const Camera2D& getCamera() const {return m_camera;};

    private:
        bool m_valid{false};
        int m_viewportWidth{};
        int m_viewportHeight{};
        Window* m_renderWindow{nullptr};

        Camera2D m_camera{};


        // Temporary variables
        std::unique_ptr<QuadMesh> m_spriteMesh {nullptr};
        Shader m_spriteShader{};

        // Model matrices of every sprite drawn this frame, uploaded to the SSBO in one go
        GLBufferObject m_modelMatrixSSBO{};
        // Current size of the SSBO's storage in bytes, so we only reallocate when it needs to grow
        size_t m_modelMatrixSSBOCapacity{0};
        std::vector<glm::mat4> m_modelMatrices{};

        // Callback functions and bindings
        ScopedBinding<int, int> WindowResizedBinding{};
        void onWindowResized(int width, int height);

    };
}
