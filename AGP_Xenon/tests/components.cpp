#include <algorithm>
#include <catch2/catch_test_macros.hpp>

#include "AGP_Engine/Core/Engine.h"
#include "AGP_Engine/Core/Level.h"
#include "AGP_Engine/Core/ECS/Components/SpriteRenderer.h"

TEST_CASE("Components are added") {
    AGPEngine::Engine e{100, 100, "", false};
    AGPEngine::Level testLevel{};
    auto* ent = testLevel.createEntity();
    auto* comp = ent->addComponent<AGPEngine::SpriteRenderer>();
    //REQUIRE(testLevel.m_entities.size() == 1);
    //REQUIRE(ent->m_components.size() == 2);
    REQUIRE(ent->hasComponent<AGPEngine::SpriteRenderer>());
}