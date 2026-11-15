#pragma once

#include <string>

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

        // TODO: Temporary variables, should be wrapped or removed
        SDL_Window* window {nullptr};

    private:
        // Engine has been initialized and is in a valid state to be destroyed
        bool valid{};

    };
}
