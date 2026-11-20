#pragma once


#include "SDL3/SDL_video.h"

#include <expected>
#include <string>

namespace AGPEngine {

    class Window {

    public:
        Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) noexcept;
        Window& operator=(Window&&) noexcept;

        ~Window();

        struct Error {
            [[maybe_unused]] std::string message{};
        };

        // Initialization for the overall window backend to allow creation of windows
        // Must be called before any window creation
        static void InitializeBackend();
        // Window creation may fail, expected to error handle on failure
        static std::expected<Window, Error> Create(const std::string& title, int w, int h);
        static void CleanupBackend();

    private:
        // Private constructor to easily construct from SDL windows
        explicit Window(SDL_Window* sdlWindow): m_sdlWindow(sdlWindow){}

    public:
        [[nodiscard]] SDL_Window* getNativeWindow() const{return m_sdlWindow;}
    private:
        SDL_Window* m_sdlWindow{nullptr};
        static bool BackendIsInitialized;
    };
}

static AGPEngine::Window::Error InitFailed {"AGP_ENGINE: Window backend initialization failed.\n"};
static AGPEngine::Window::Error CreateFailed {"AGP_ENGINE: Window creation failed.\n"};
