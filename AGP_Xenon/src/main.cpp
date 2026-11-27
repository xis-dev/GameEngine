
#include "AGP_Engine/Core/Engine.h"
#include <iostream>

#include "AGP_Engine/Core/Level.h"
#include "AGP_Engine/Core/ECS/Components/SpriteRenderer.h"


struct TestComponent: public AGPEngine::Component {

    TestComponent(float testParams);
    void onBegin() override;
    void update(float deltaTime) override;
    void onDestroy() override;
};

TestComponent::TestComponent(float testParams) {
    std::cout << "Test Component Param value: " << testParams << std::endl;
}

void TestComponent::onBegin() {
    Component::onBegin();
    std::cout << "Test Component: Begin" << std::endl;
}

void TestComponent::update(float deltaTime) {
    Component::update(deltaTime);
    std::cout << "Test Component: Update" << std::endl;
}

void TestComponent::onDestroy() {
    Component::onDestroy();
    std::cout << "Test Component: Destroy" << std::endl;
}

class BasicLevel: public AGPEngine::Level {

public:
    void onBegin() override;
    void update(float deltaTime) override;
};


void BasicLevel::onBegin() {
    createEntity("basic");
    auto* basicEnt = getEntity("basic");
    basicEnt->addComponent<AGPEngine::SpriteRenderer>();
    basicEnt->addComponent<TestComponent>(1.0f);

    Level::onBegin();
}

void BasicLevel::update(float deltaTime) {
    Level::update(deltaTime);
}

void AGPEngine::createGame() {
   Engine e{500, 500, "AGPEngine", false};

    BasicLevel testLevel{};
    e.run(testLevel);
}



