//
// Created by seer on 11/5/26.
//

#include "../../include/AGP_Engine/Graphics/Renderer.h"

void AGPEngine::Renderer::SetRenderContext(const Window &win) {

    // SDL Context setting
    SDL_GL_CreateContext(win.getNativeWindow());

}

void AGPEngine::Renderer::SwapBuffer(const Window &win) {

    // SDL window swapping
    SDL_GL_SwapWindow(win.getNativeWindow());

}
