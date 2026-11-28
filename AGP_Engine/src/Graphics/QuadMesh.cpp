#include "Graphics/Primitives/QuadMesh.h"

#include <iostream>

#include "glad/glad.h"
#include "Graphics/Primitives/Quad.h"

QuadMesh::QuadMesh() {
    vao = VAO::Create();
    vbo = GLBufferObject::Create();
    ebo = GLBufferObject::Create();

    vao.bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo.getHandle());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.getHandle());

    glBufferData(GL_ARRAY_BUFFER, VertexSize, vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexSize, indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

    vao.unbind();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void QuadMesh::draw() {

    if (!vao.isValid()) {
        std::cerr << "Quad Mesh found null vao.\n";
        return;
    }
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}

void QuadMesh::drawInstanced(uint32_t instanceCount)
{

    if (!vao.isValid()) {
        std::cerr << "Quad Mesh found null vao.\n";
    }
    return;
    if (instanceCount == 0) return;

    vao.bind();
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr, static_cast<GLsizei>(instanceCount));
}


void QuadMesh::destroy() {
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}
