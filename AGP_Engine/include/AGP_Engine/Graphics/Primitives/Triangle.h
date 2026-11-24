#pragma once
#include "Graphics/Vertex.h"


struct Triangle {
    static constexpr Vertex vertices[3] {
        {.position = {-1.0f, -1.0f, 0.0f}},
        {.position = { 0.0f,  1.0f, 0.0f}},
        {.position = { 1.0f, -1.0f, 0.0f}},
    };
};
