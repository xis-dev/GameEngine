#pragma once
#include "../Resources/Resource.h"

class VAO: public GPUResource {

public:
    VAO() = default;

    VAO(VAO&&) = default;
    VAO& operator=(VAO&&) = default;

    static VAO Create();

    void bind() const;
    void unbind() const;

    void destroy() override;
};

class GLBufferObject: public GPUResource {
public:
    GLBufferObject() = default;

    GLBufferObject(GLBufferObject&&) = default;
    GLBufferObject& operator=(GLBufferObject&&) = default;

    static GLBufferObject Create();

    // TODO: Binding and buffer data
    void destroy() override;
};