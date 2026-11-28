//
// Created by seer on 11/5/26.
//

#include "../../include/AGP_Engine/Graphics/Renderer.h"

#include <algorithm>
#include <filesystem>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
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

        //TODO: Handle pixel color be handled as transparent (for the Xenon 2000 sprites)
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        onResize(vpWidth, vpHeight);


        // Init triangle shader
        m_spriteShader = Shader(std::filesystem::path(SHADER_DIR).string() + "quad.vert", std::filesystem::path(SHADER_DIR).string() + "textured_quad.frag");
        if (!m_spriteShader.isValid())
        {
            std::cerr << "AGP_ENGINE::RENDERER: Failed to load shaders.\n";
        }
        m_spriteMesh = std::make_unique<QuadMesh>();

        m_modelMatrixSSBO = GLBufferObject::Create();
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_modelMatrixSSBO.getHandle());

        m_valid = true;

        // TODO: Temp ssbo generation
        m_modelMatrixSSBO = GLBufferObject::Create();

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_modelMatrixSSBO.getHandle());
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_modelMatrixSSBO.getHandle());
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

    void Renderer::render(const Level& level)
    {

        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*if (m_valid) {
            // 1. Gather one model matrix per drawable entity. Everything is a sprite on the same quad,
            //    so the matrices are all the GPU needs to know to place them.
            m_modelMatrices.clear();
            for (const auto& ent: level.getEntities()) {
                if (!ent->isAlive() || !ent->transform || !ent->hasComponent<SpriteRenderer>()) continue;
                m_modelMatrices.push_back(ent->transform->getTransform());
            }

            if (!m_modelMatrices.empty()) {
                // 2. Upload them in one go. Only reallocate the buffer when it has to grow.
                const size_t bytes = m_modelMatrices.size() * sizeof(glm::mat4);
                glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_modelMatrixSSBO.getHandle());
                if (bytes > m_modelMatrixSSBOCapacity) {
                    // Grow geometrically so spawning lots of entities doesn't reallocate every frame
                    m_modelMatrixSSBOCapacity = std::max(bytes, m_modelMatrixSSBOCapacity * 2);
                    glBufferData(GL_SHADER_STORAGE_BUFFER, static_cast<GLsizeiptr>(m_modelMatrixSSBOCapacity), nullptr, GL_DYNAMIC_DRAW);
                }
                glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, static_cast<GLsizeiptr>(bytes), m_modelMatrices.data());
                glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_modelMatrixSSBO.getHandle());

                // 3. One draw call for every sprite
                m_spriteShader.use();
                glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(m_camera.getViewProjection()));
                m_spriteMesh->drawInstanced(static_cast<uint32_t>(m_modelMatrices.size()));
            }
        }

        m_renderWindow->swapBuffers();
    };*/

        glUseProgram(m_spriteShader.getHandle());

        int renderInstance = 0;
        for (const auto& ent: level.getEntities()) {

            if (ent->hasComponent<Transform>() && ent->hasComponent<SpriteRenderer>()) {
                // Only push back once there's too many instances to render
                if (renderInstance >= m_modelMatrices.size()) {
                    m_modelMatrices.push_back(ent->transform->getTransform());
                }
                else {
                   m_modelMatrices[renderInstance] = ent->transform->getTransform();
                }
                ++renderInstance;
            }

            glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_modelMatrixSSBO.getHandle());
            glBufferData(GL_SHADER_STORAGE_BUFFER, m_modelMatrices.size() * sizeof(glm::mat4), m_modelMatrices.data(), GL_DYNAMIC_DRAW);

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

