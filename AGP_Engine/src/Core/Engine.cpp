#include "Core/Engine.h"
#include <algorithm>
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
        shutdown();
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
    //m_window->OnClosed.bindFunction(this, &Engine::shutdown);
    m_window->setVsync(true);

    int pixelW = winWidth;
    int pixelH = winHeight;
    m_window->getPixelSize(pixelW, pixelH);


    m_renderer = std::make_unique<Renderer>(m_window.get(), winWidth, winHeight);
    if (!m_renderer || !m_renderer->isValid())
    {
        std::cerr << "AGP_ENGINE: Engine Initialization Failed: Renderer could not be created.\n";
        m_renderer->destroy();
        m_renderer.reset();
        m_window.reset();
        Window::CleanupBackend();
        valid = false;
        return valid;
    }


    //Renderer::Init();
    valid = true;
    return valid;
    

   
}

void Engine::run(Level& level) {

    if (!valid) {
        std::cerr << "AGP_ENGINE: Engine cannot run in an invalid state! It likely has not been initialized or failed to initialize.\n";
        return;
    }

    // Deltatime measured with the high res counter
    const auto  counterFrequency = static_cast<double>(SDL_GetPerformanceFrequency());
    uint64_t lastCounter = SDL_GetPerformanceCounter();

    // Cap Deltatime at 1s, so dragging the window or hitting a breakpoint doesn't result in a huge update when the loop resumes
    constexpr float MaxDeltaTime = 0.1f;


    level.onGameBegin();
    while (!m_window->shouldClose()) {
        const uint64_t currentTime = SDL_GetPerformanceCounter();
        const double deltaTime = std::min(static_cast<float>(static_cast<double>(currentTime - lastCounter) / counterFrequency), MaxDeltaTime);

        m_window->pollEvents();

        level.update(deltaTime);
        m_renderer->render(level);

        level.updateEnd();
    }
}

void Engine::shutdown() {

    //Renderer::Shutdown();

    m_renderer->destroy();
    m_window->destroy();
    Window::CleanupBackend();

    valid = false;
    
}

bool Engine::isValid() const { return valid; }
