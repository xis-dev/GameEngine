//
// Created by seer on 11/5/26.
//


#include "../../include/AGP_Engine/Graphics/Renderer.h"

#include <filesystem>
#include <glad/glad.h>
#include <iostream>
#include "AGP_Engine/Utility/Utility.h"
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

    void Renderer::update() {

        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_spriteShader.getHandle());

        m_spriteMesh->draw();
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

