// src/Core/Window.cpp
#include "Core/Window.h"
#include <SDL3/SDL.h>
#include <iostream>

namespace AGPEngine {

bool Window::BackendIsInitialized = false;

std::expected<Window, Error> Window::Create(const std::string& title, int w, int h) {
    if (!BackendIsInitialized) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            return std::unexpected{ Error{ std::string("SDL_Init failed: ") + SDL_GetError() } };
        }
        BackendIsInitialized = true;
    }

    // Request GL 3.3 Core BEFORE window creation
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* win = SDL_CreateWindow(title.c_str(), w, h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!win) {
        return std::unexpected{ Error{ std::string("SDL_CreateWindow failed: ") + SDL_GetError() } };
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(win);
    if (!ctx) {
        SDL_DestroyWindow(win);
        return std::unexpected{ Error{ std::string("SDL_GL_CreateContext failed: ") + SDL_GetError() } };
    }

    SDL_GL_MakeCurrent(win, ctx);
    SDL_GL_SetSwapInterval(1);   // vsync

    return Window{ win, ctx };
}

void Window::CleanupBackend() {
    if (BackendIsInitialized) {
        SDL_Quit();
        BackendIsInitialized = false;
    }
}

void* Window::GetProcAddress(const char* name) const {
    return reinterpret_cast<void*>(SDL_GL_GetProcAddress(name));
}
void Window::MakeCurrent() const  { SDL_GL_MakeCurrent(m_sdlWindow, m_glContext); }
void Window::SwapBuffers() const  { SDL_GL_SwapWindow(m_sdlWindow); }
void Window::GetSize(int& w, int& h) const { SDL_GetWindowSize(m_sdlWindow, &w, &h); }

Window::~Window() {
    if (m_glContext) SDL_GL_DestroyContext(m_glContext);
    if (m_sdlWindow) SDL_DestroyWindow(m_sdlWindow);
}
Window::Window(Window&& w) noexcept
    : m_sdlWindow(std::exchange(w.m_sdlWindow, nullptr))
    , m_glContext(std::exchange(w.m_glContext, nullptr)) {}

Window& Window::operator=(Window&& w) noexcept {
    if (this != &w) {
        if (m_glContext) SDL_GL_DestroyContext(m_glContext);
        if (m_sdlWindow) SDL_DestroyWindow(m_sdlWindow);
        m_sdlWindow = std::exchange(w.m_sdlWindow, nullptr);
        m_glContext = std::exchange(w.m_glContext, nullptr);
    }
    return *this;
}

} // namespace AGPEngine