//
// Created by seer on 11/5/26.
//

#include "../../include/AGP_Engine/Graphics/Renderer.h"

#include <filesystem>
#include <glad/glad.h>
#include <iostream>
#include "AGP_Engine/Utility/Utility.h"
#include "Core/ECS/Components/SpriteRenderer.h"
#include "Graphics/Primitives/Quad.h"
#include "Graphics/Primitives/Triangle.h"

namespace  AGPEngine
{
    Renderer::Renderer(Window* win, int vpWidth, int vpHeight):
        m_viewportWidth(vpWidth), m_viewportHeight(vpHeight)
    {
        AGPASSERT(win != nullptr, "AGP_ENGINE::RENDERER: Found nullptr window while creating renderer.");

        changeContextWindow(win);

        // Lazy load glad
        static bool gladLoaded = [] {
            return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(Window::GetProcAddress));
        }();

        if (!gladLoaded) {
            std::cerr << "AGP_ENGINE::RENDERER: GLAD failed to load on initialization and renderers cannot be created.\n";
            return;
        }

        glViewport(0, 0, vpWidth, vpHeight);

        // Init triangle shader
        m_spriteShader = Shader(std::filesystem::path(SHADER_DIR).string() + "triangle.vert", std::filesystem::path(SHADER_DIR).string() + "triangle.frag");
        m_spriteMesh = std::make_unique<QuadMesh>();

        // TODO: Temp ssbo generation
        glGenBuffers(1, &ssbo);

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

        m_spriteShader.use();
    }

    void Renderer::Init()
    {
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        std::cout << "GL_VERSION: " << (version ? reinterpret_cast<const char*>(version) : "null") << "\n";
        std::cout << "GL_RENDERER: " << (renderer ? reinterpret_cast<const char*>(renderer) : "null") << "\n";
    }

    void Renderer::Shutdown()
    {
        //TODO: VAO and VBO cleanup here (no leaks)
    }

    void Renderer::render(const Level& level) {

        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_spriteShader.getHandle());

        int renderInstance = 0;
        for (const auto& ent: level.getEntities()) {

            if (ent->hasComponent<Transform>() && ent->hasComponent<SpriteRenderer>()) {
                modelMatrices.push_back(ent->transform->getTransform());
            }

            glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
            glBufferData(GL_SHADER_STORAGE_BUFFER, modelMatrices.size() * sizeof(glm::mat4), modelMatrices.data(), GL_DYNAMIC_DRAW);

            m_spriteMesh->draw();
            // TODO: Change this, probably cache sprite renderer entities
            // if (lastRenderCount < level.getEntities().size()) {
            //     lastRenderCount = level.getEntities().size();
            //
            //
            // }
        }

        m_renderWindow->swapBuffers();
    }

    void Renderer::destroy() {

        m_spriteMesh->destroy();
        m_spriteShader.destroy();
    }

    void Renderer::changeContextWindow(Window* win){
        if (!win) {
            std::cerr << "AGP_ENGINE::RENDERER: Found null window while changing renderer context window.\n";
            return;
        }
        Window::MakeRenderContext(*win);
        m_renderWindow = win;
    }
}

