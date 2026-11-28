#pragma once


#include <SDL3/SDL.h>
#include <expected>
#include <string>

#include "AGP_Engine/Utility/Utility.h"

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
        
        // Window creation may fail, expected to error handle on failure
        [[nodiscard]]static std::expected<Window, Error<Window>> Create(const std::string& title, int w, int h);
        static void CleanupBackend();
        [[nodiscard]] static void* GetProcAddress(const char* name) ;
        static void MakeRenderContext(const Window& window);

        void swapBuffers() const;
        [[nodiscard]] SDL_Window* getNativeWindow() const { return m_sdlWindow; }
        void getSize(int& w, int& h) const;
        void getPixelSize(int& w, int& h) const;
        void setVsync(bool on);

        [[nodiscard]] bool isValid() const;

        void destroy();

    private:
        // Private constructor to easily construct from SDL windows
        explicit Window(SDL_Window* sdlWindow, SDL_GLContext sdlContext): m_sdlWindow(sdlWindow), m_glContext(sdlContext){}


    private:
        SDL_Window* m_sdlWindow{nullptr};
        SDL_GLContext m_glContext{nullptr};
        static bool BackendIsInitialized;
    };
}

