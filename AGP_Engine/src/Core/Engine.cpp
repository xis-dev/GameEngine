//
// Created by seer on 11/5/26.
//

#include "Core/Engine.h"

#include <iostream>

#include "SDL3/SDL.h"

#include "Utility.h"

#include <glad/glad.h>

AGPEngine::Engine::Engine(int winWidth, int winHeight, const std::string &winTitle, bool runOnInit) {

    if (!init(winWidth, winHeight, winTitle)) {
        return;
    }

    if (runOnInit) { run(); }

}

AGPEngine::Engine::~Engine() {
    if (valid) {
        cleanup();
    }
}

bool AGPEngine::Engine::init(int winWidth, int winHeight, const std::string &winTitle) {

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(winTitle.c_str(), winWidth, winHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << "AGP_ENGINE: Failed to initialize engine, could not create window.\n";
        SDL_Quit();
        valid = false;
        return valid;
    }

    // Set current context
    SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)(SDL_GL_GetProcAddress)))
    {
        std::cerr << "AGP_ENGINE: Failed to initialize engine, could not initialize glad.\n";
        SDL_Quit();
        valid = false;
        return valid;
    }

    valid = true;
    return valid;

}

void AGPEngine::Engine::run() {

    if (!valid) {
        std::cerr << "AGP_ENGINE: Engine cannot run in an invalid state, it likely has not been initialized or failed to initialize.\n";
        return;
    }

    bool running = true;
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

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }
}

void AGPEngine::Engine::cleanup() {

    SDL_DestroyWindow(window);
    SDL_Quit();

    valid = false;
}
