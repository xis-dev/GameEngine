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
            std::string message{};
        };

        // Initialization for the overall window backend to allow creation of windows
        // Must be called before any window creation
        static void InitializeBackend();
        
        // Window creation may fail, expected to error handle on failure
        [[nodiscard]]static std::expected<Window, Error> Create(const std::string& title, int w, int h);
        static void CleanupBackend();

        
        
        [[nodiscard]] void* GetProcAddress(const char* name) const;
        void MakeCurrent() const;
        void SwapBuffers() const;
        void GetSize(int& w, int& h) const;

        [[nodiscard]] SDL_Window* getNativeWindow() const { return m_sdlWindow; }

        
        
    private:
        // Private constructor to easily construct from SDL windows
        explicit Window(SDL_Window* sdlWindow, SDL_GLContext sdlContext): m_sdlWindow(sdlWindow), m_glContext(sdlContext){}

   
    private:
        SDL_Window* m_sdlWindow{nullptr};
        SDL_GLContext m_glContext{nullptr};
        static bool BackendIsInitialized;
    };
}

static AGPEngine::Window::Error InitFailed {"AGP_ENGINE: Window backend initialization failed.\n"};
static AGPEngine::Window::Error CreateFailed {"AGP_ENGINE: Window creation failed.\n"};
