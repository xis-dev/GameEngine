
#include "AGP_Engine/Core/Engine.h"
#include <iostream>

#include "AGP_Engine/Core/Level.h"
#include "AGP_Engine/Core/ECS/Components/SpriteRenderer.h"

static void BuildLevel()
{


}


int main() {
    AGPEngine::Engine e{500, 500, "AGPEngine", false};

//    BuildLevel();
    AGPEngine::Level testLevel{};
    auto* testEnt = testLevel.createEntity();
    testEnt->addComponent<AGPEngine::SpriteRenderer>();
    e.run(testLevel);

}



