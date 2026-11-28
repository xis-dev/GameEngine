#include "Graphics/GLObjects.h"

#include "glad/glad.h"


VAO VAO::Create() {
    VAO out;
    glGenVertexArrays(1, &out.m_handle);
    return out;
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

GLBufferObject GLBufferObject::Create() {
    GLBufferObject out;
    glGenBuffers(1, &out.m_handle);
    return out;
}

void GLBufferObject::destroy() {
    if (m_handle != InvalidHandle) {
        glDeleteBuffers(1, &m_handle);
        m_handle = InvalidHandle;
    }
}
