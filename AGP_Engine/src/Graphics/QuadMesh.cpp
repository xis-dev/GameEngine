#include "Graphics/Primitives/QuadMesh.h"

#include <iostream>

#include "glad/glad.h"
#include "Graphics/Primitives/Quad.h"

QuadMesh::QuadMesh() {
    vao = std::make_unique<VAO>();
    vbo = std::make_unique<GLBufferObject>();
    ebo = std::make_unique<GLBufferObject>();

    vao->bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo->getHandle());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->getHandle());

    glBufferData(GL_ARRAY_BUFFER, Quad::VertexSize, Quad::vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Quad::IndexSize, Quad::indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    vao->unbind();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void QuadMesh::draw() {

    if (!vao) {
        std::cerr << "Quad Mesh found nullptr vao.\n";
        return;
    }
    vao->bind();
    glDrawElements(GL_TRIANGLES, Quad::indices.size(), GL_UNSIGNED_INT, nullptr);
}

void QuadMesh::destroy() {
    vao->destroy();
    vbo->destroy();
    ebo->destroy();
}
