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

    class SpriteRenderer: public Component
    {
    public:
        SpriteRenderer(Shader &shader);
        ~SpriteRenderer();


        GLuint loadTexture(char* filename);

        void DrawSprite(auto &texture, glm::vec2 position,
            glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
            glm::vec3 color = glm::
            vec3(1.0f));

    private:
        Shader       shader;
        unsigned int quadVAO;

        void initRenderData();

    };

    class Animator: public Component
    {


        Animator(Shader &shader, SpriteRenderer renderer, int width, int height, int fps);
        ~Animator();

    virtual void update(float deltaTime);

    };


}

