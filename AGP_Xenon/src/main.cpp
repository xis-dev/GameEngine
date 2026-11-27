
#include "AGP_Engine/Core/Engine.h"
#include <iostream>

#include "AGP_Engine/Core/Level.h"
#include "AGP_Engine/Core/ECS/Components/SpriteRenderer.h"

class BasicLevel: public AGPEngine::Level {

public:
    void onBegin() override;
    void update(float deltaTime) override;
};

void BasicLevel::onBegin() {
    Level::onBegin();
    createEntity("basic");
    auto* basicEnt = getEntity("basic");
    basicEnt->addComponent<AGPEngine::SpriteRenderer>();
}

void BasicLevel::update(float deltaTime) {
    Level::update(deltaTime);
    std::cout << "Basic ent" << std::endl;
}

int main() {
    AGPEngine::Engine e{500, 500, "AGPEngine", false};

    BasicLevel testLevel{};
    e.run(testLevel);

}



