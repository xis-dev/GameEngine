//
// Created by seer on 11/5/26.
//

#include "Core/Window.h"

#include <iostream>
#include <optional>
#include <utility>

#include "SDL3/SDL_init.h"

namespace AGPEngine {

    bool Window::BackendIsInitialized = false;

    void Window::InitializeBackend() {
        if (!BackendIsInitialized) {
            SDL_Init(SDL_INIT_VIDEO);
        }
    }

    std::optional<Window> Window::Create(const std::string& title, int w, int h) {

        // Lazy initialize backend
        if (!BackendIsInitialized) {
            InitializeBackend();
        }

        // SDL Window creation
        SDL_Window* sdlWin = SDL_CreateWindow(title.c_str(), w, h,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        return Window{sdlWin};

    }

    void Window::CleanupBackend() {
        if (BackendIsInitialized) {
            SDL_Quit();
        }
    }

    Window::Window(Window && w) noexcept:
        m_sdlWindow(std::exchange(w.m_sdlWindow, nullptr)){}

    Window & Window::operator=(Window&& w) noexcept {

        if (this != &w) {
            // Cleanup if this object was already a valid window
            if (m_sdlWindow) SDL_DestroyWindow(m_sdlWindow);

            m_sdlWindow = std::exchange(w.m_sdlWindow, nullptr);
        }

        return *this;
    }

    Window::~Window() {
        if (m_sdlWindow) {
            SDL_DestroyWindow(m_sdlWindow);
        }
    }
}
