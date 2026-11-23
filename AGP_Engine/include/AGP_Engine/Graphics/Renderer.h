#pragma once
#include "Core/Window.h"

namespace AGPEngine {

    class Renderer {

    public:
        
        static void     Init();
        static void Shutdown();
        
        //Moved SwapBuffers and SetRendercontext to Window. This way we have to handle less files and Windows takes care of these issues
    };
}
