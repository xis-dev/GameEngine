#pragma once

#include <memory>
#include <string>

#include "Window.h"
#include "AGP_Engine/Graphics/Renderer.h"

namespace AGPEngine{
    // Start point
    void createGame();
}

namespace AGPEngine {
    class Engine {

    public:
        Engine(int winWidth, int winHeight, const std::string& winTitle, bool runOnInit = true);
        ~Engine();

        bool init(int winWidth, int winHeight, const std::string &winTitle);
        void run(Level &level);
        void shutdown();

        [[nodiscard]] bool isValid() const;


        // Only works if isValid() is true. We can reach the camera via getRenderer().getCamera()
        [[nodiscard]] Renderer& getRenderer() { return *m_renderer; }

    private:
        // Engine has been initialized and is in a valid state to be destroyed
        bool valid{};

        std::unique_ptr<Window> m_window{nullptr};
        std::unique_ptr<Renderer> m_renderer{nullptr};
    };
}
