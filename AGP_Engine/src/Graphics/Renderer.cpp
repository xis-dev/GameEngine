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
        triangleShader = Shader(std::filesystem::path(SHADER_DIR).string() + "triangle.vert", std::filesystem::path(SHADER_DIR).string() + "triangle.frag");

        // Init temp vao and vbo
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, Quad::vertices.size() * sizeof(Vertex), Quad::vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Quad::indices.size() * sizeof(uint32_t), Quad::indices.data(), GL_STATIC_DRAW);

        // Position attribute description and enable
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glEnableVertexAttribArray(0);

        // Unbind vao & vbo
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glUseProgram(triangleShader.getHandle());

        // Draw triangle
        glDrawElements(GL_TRIANGLES, Quad::indices.size(), GL_UNSIGNED_INT, nullptr);

        m_renderWindow->swapBuffers();
    }

    void Renderer::destroy() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);

        triangleShader.destroy();
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

