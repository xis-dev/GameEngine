#include "Graphics/GLObjects.h"

#include "glad/glad.h"

VAO::VAO() {
    glGenVertexArrays(1, &m_handle);
}


void VAO::bind() const {
    glBindVertexArray(m_handle);
}

void VAO::unbind() const{
    glBindVertexArray(0);
}

void VAO::destroy() {
    if (m_handle != InvalidHandle) {
        glDeleteVertexArrays(1, &m_handle);
        m_handle = InvalidHandle;
    }
}

GLBufferObject::GLBufferObject() {
    glGenBuffers(1, &m_handle);
}

void GLBufferObject::destroy() {
    glDeleteBuffers(1, &m_handle);
}
