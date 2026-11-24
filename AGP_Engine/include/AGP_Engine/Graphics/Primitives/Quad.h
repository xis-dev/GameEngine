#pragma once
#include <vector>

#include "AGP_Engine/Graphics/Vertex.h"

struct Quad {
     static constexpr std::array<Vertex, 4> vertices = {
         Vertex{.position = { 1.0f, -1.0f, 0.0f}},
         Vertex{.position = { 1.0f,  1.0f, 0.0f}},
         Vertex{.position = {-1.0f,  1.0f, 0.0f}},
         Vertex{.position = {-1.0f, -1.0f, 0.0f}}
    };

    static constexpr std::array<uint32_t, 6> indices = {
        0, 1, 2,
        3, 0, 2
    };
};

