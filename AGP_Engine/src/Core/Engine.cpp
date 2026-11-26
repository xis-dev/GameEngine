#include "Core/Engine.h"
#include <iostream>
#include "SDL3/SDL.h"
#include "Graphics/Renderer.h"


using namespace AGPEngine;
Engine::Engine(int winWidth, int winHeight, const std::string &winTitle, bool runOnInit) {

    if (!init(winWidth, winHeight, winTitle)) {
        return;
    }

    //if (runOnInit) { run(TODO); }

}

Engine::~Engine() {
    if (valid) {
        cleanup();
    }
}

bool Engine::init(int winWidth, int winHeight, const std::string &winTitle) {

    auto win = Window::Create(winTitle, winWidth, winHeight);
    if (!win) {
        std::cerr << "AGP_ENGINE: Failed to initialize engine.\n" << win.error().message << "\n";
        valid = false;
        return valid;
    }

    m_window = std::make_unique<Window>(std::move(win.value()));
    m_renderer = std::make_unique<Renderer>(m_window.get(), winWidth, winHeight);
    
    //Renderer::Init();
    valid = true;
    return valid;
    

   
}

void Engine::run(const Level& level) {

    if (!valid) {
        std::cerr << "AGP_ENGINE: Engine cannot run in an invalid state! It likely has not been initialized or failed to initialize.\n";
        return;
    }

    bool running = true;
    // TODO: This goes into input manager when it exists
    SDL_Event event;

    while (running) {

        // SDL Event handling
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                    // Key events
                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_ESCAPE)
                        running = false;
                    break;

                default:
                    break;
            }
        }

        m_renderer->render(level);
    }
}

void Engine::cleanup() {

    //Renderer::Shutdown();

    m_renderer->destroy();
    m_window->destroy();
    Window::CleanupBackend();
    
}

bool Engine::isValid() const { return valid; }
