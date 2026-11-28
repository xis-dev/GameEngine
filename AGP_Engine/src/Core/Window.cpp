#include "Core/Window.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <utility>

#include "Utility/Utility.h"

namespace AGPEngine {

bool Window::BackendIsInitialized = false;

void Window::startCloseWindow() {
    m_shouldClose = true;
    OnClosed.broadcast();
}


std::expected<Window, Error<Window>> Window::Create(const std::string& title, int width, int height) {
    if (!BackendIsInitialized) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            return std::unexpected{ Error<Window>{ .message = std::string("SDL_Init failed: ") + SDL_GetError() } };
        }
        BackendIsInitialized = true;
    }

    // Request GL 4.3 Core BEFORE window creation
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


#ifdef DEBUG
    // Debug context so the driver reports GL errors through the debug callback
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

    SDL_Window* win = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!win) {
        return std::unexpected{ Error<Window>{ .message = std::string("SDL_CreateWindow failed: ") + SDL_GetError() } };
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(win);
    if (!ctx) {
        SDL_DestroyWindow(win);
        return std::unexpected{ Error<Window>{ .message = std::string("SDL_GL_CreateContext failed: ") + SDL_GetError() } };
    }

    return Window{ win, ctx };
}

void Window::CleanupBackend() {
    if (BackendIsInitialized) {
        SDL_Quit();
        BackendIsInitialized = false;
    }
}

void* Window::GetProcAddress(const char* name) {
    return reinterpret_cast<void*>(SDL_GL_GetProcAddress(name));
}
void Window::MakeRenderContext(const Window& win)  { SDL_GL_MakeCurrent(win.m_sdlWindow, win.m_glContext); }
void Window::swapBuffers() const  { SDL_GL_SwapWindow(m_sdlWindow); }
void Window::getSize(int& w, int& h) const { SDL_GetWindowSize(m_sdlWindow, &w, &h); }
void Window::getPixelSize(int& w, int& h) const { SDL_GetWindowSizeInPixels(m_sdlWindow, &w, &h); }


void Window::setVsync(bool on) {
    // Only matters if it's the current context
    if (m_glContext == SDL_GL_GetCurrentContext()) {
        SDL_GL_SetSwapInterval(on);   // vsync
    }

}

bool Window::isValid() const { return m_sdlWindow != nullptr;}

void Window::destroy() {
    if (m_glContext) {
        SDL_GL_DestroyContext(m_glContext);
        m_glContext = nullptr;
    }
    if (m_sdlWindow) {
        SDL_DestroyWindow(m_sdlWindow);
        m_sdlWindow = nullptr;
    }
}

void Window::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                startCloseWindow();
                break;

            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                OnResized.broadcast(event.window.data1, event.window.data2);
                break;

                // TODO: These would actually be abstracted in input manager and then window subscribes to those
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_ESCAPE) {
                    OnClosed.broadcast();
                }
                break;

            default:
                break;
        }
    }
}

bool Window::shouldClose() const {return m_shouldClose;}

Window::~Window() {
    if (isValid()) {
        destroy();
    }
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