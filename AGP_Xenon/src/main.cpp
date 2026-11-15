
#include "AGP_Engine/Core/Engine.h"

#include <iostream>

int main() {
    AGPEngine::Engine e{};

    e.init(1, 1, "NOO");
    e.run();
    e.cleanup();

}