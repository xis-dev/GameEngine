#pragma once

#include <array>
#include <cstdint>
#include <memory>

#include "AGP_Engine/Graphics/GLObjects.h"
#include "AGP_Engine/Resources/Resource.h"
#include "AGP_Engine/Graphics/Vertex.h"

namespace AGPEngine {

}

class QuadMesh {

public:
    QuadMesh();

private:
    VAO vao{};
    GLBufferObject vbo{};
    GLBufferObject ebo{};
public:
    void draw();
    void drawInstanced(uint32_t instanceCount); //Draw instanceCount copies of the same quad in one call (gl_InstanceID uses the model matrix)
    void destroy();

private:

    static constexpr std::array<Vertex, 4> vertices = {
        Vertex{.position = { 1.0f, -1.0f, 0.0f}, .uv = {1.0f, 0.0f}},
        Vertex{.position = { 1.0f,  1.0f, 0.0f}, .uv = {1.0f, 1.0f}},
        Vertex{.position = {-1.0f,  1.0f, 0.0f}, .uv = {0.0f, 1.0f}},
        Vertex{.position = {-1.0f, -1.0f, 0.0f}, .uv = {0.0f, 0.0f}}
    };

    static constexpr std::array<uint32_t, 6> indices = {
        0, 1, 2,
        3, 0, 2
    };

    static constexpr uint32_t IndexSize = sizeof(indices[0]) * indices.size();
    static constexpr uint32_t VertexSize = sizeof(vertices[0]) * vertices.size();

};
