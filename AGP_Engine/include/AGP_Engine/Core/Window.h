#pragma once

#include <optional>
#include <string>

#include "SDL3/SDL_video.h"

namespace AGPEngine {

    class Window {

    public:
        Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        Window(Window&&) noexcept;
        Window& operator=(Window&&) noexcept;

        ~Window();

        // Initialization for the overall window backend to allow creation of windows
        // Must be called before any window creation
        static void InitializeBackend();
        // Window creation may fail, optional to error handle on failure
        // TODO: Not 100% on using optional here, could use boolean + reference
        static std::optional<Window> Create(const std::string& title, int w, int h);
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
