#pragma once
#include <cstdint>
#include <memory>

#include "AGP_Engine/Graphics/GLObjects.h"
#include "AGP_Engine/Resources/Resource.h"

namespace AGPEngine {

}

class QuadMesh {

public:
    QuadMesh();

private:
    std::unique_ptr<VAO> vao{nullptr};
    std::unique_ptr<GLBufferObject> vbo{nullptr};
    std::unique_ptr<GLBufferObject> ebo{nullptr};

public:
    void draw();
    void destroy();

};
