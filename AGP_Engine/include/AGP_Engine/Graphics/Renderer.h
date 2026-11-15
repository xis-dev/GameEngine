#pragma once
#include "Core/Window.h"

namespace AGPEngine {

    class Renderer {

    public:
        static void SetRenderContext(const Window& win);
        static void SwapBuffer(const Window& win);
    };
}
