#pragma once
#include "../Resources/Resource.h"

class VAO: public GPUResource {

public:
    VAO();

    VAO(VAO&&) = default;
    VAO& operator=(VAO&&) = default;


    void bind() const;
    void unbind() const;

    void destroy() override;
};

class GLBufferObject: public GPUResource {
public:
    GLBufferObject();

    GLBufferObject(GLBufferObject&&) = default;
    GLBufferObject& operator=(GLBufferObject&&) = default;

    // TODO: Binding and buffer data

    void destroy() override;
};