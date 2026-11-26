#pragma once

#include <cstdio>

#include "Component.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "Graphics/Renderer.h"
#include "stb_image/stb_image.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_opengl.h"

namespace AGPEngine {
    class Animator: public Component
    {
        Animator(Shader &shader, SpriteRenderer renderer, int width, int height, int fps);
        ~Animator();

    public:
        void update(float deltaTime) override;

    };
}
