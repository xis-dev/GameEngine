//
// Created by seer on 11/5/26.
//


#include "../../include/AGP_Engine/Graphics/Renderer.h"
#include <glad/glad.h>
#include <iostream>

namespace  AGPEngine
{
    void Renderer::Init() 
    {
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        std::cout << "GL_VERSION: " << (version ? reinterpret_cast<const char*>(version) : "null") << "\n";
        std::cout << "GL_RENDERER: " << (renderer ? reinterpret_cast<const char*>(renderer) : "null") << "\n";
    }

    void Renderer::Shutdown()
    {
        //TODO: VAO and VBO cleanup here (no leaks)
    }
}

