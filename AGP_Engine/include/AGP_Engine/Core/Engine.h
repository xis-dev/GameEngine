#pragma once

#include <memory>
#include <string>

#include "Window.h"
#include "AGP_Engine/Graphics/Renderer.h"

namespace AGPEngine {
    class Engine {

    public:
        Engine(int winWidth, int winHeight, const std::string& winTitle, bool runOnInit = true);
        ~Engine();

        bool init(int winWidth, int winHeight, const std::string &winTitle);
        void run(const Level &level);
        void cleanup();

        [[nodiscard]] bool isValid() const;

    private:
        // Engine has been initialized and is in a valid state to be destroyed
        bool valid{};

        std::unique_ptr<Window> m_window{nullptr};
        std::unique_ptr<Renderer> m_renderer{nullptr};

    };
}
