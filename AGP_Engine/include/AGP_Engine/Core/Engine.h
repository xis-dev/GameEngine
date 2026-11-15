#pragma once

#include <string>

#include "Window.h"
#include "SDL3/SDL_video.h"

namespace AGPEngine {
    class Engine {

    public:
        Engine() = default;
        Engine(int winWidth, int winHeight, const std::string& winTitle, bool runOnInit = true);
        ~Engine();

        bool init(int winWidth, int winHeight, const std::string &winTitle);
        void run();
        void cleanup();

        // TODO: Since there is likely no editor, this could be a per level thing
        Window window;

    private:
        // Engine has been initialized and is in a valid state to be destroyed
        bool valid{};

    };
}
