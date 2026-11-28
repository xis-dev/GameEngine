//
// Created by seer on 11/25/26.
//

#include "../../../include/AGP_Engine/Core/ECS/Entity.h"

#include <ranges>

using namespace AGPEngine;


Entity::Entity(bool addTransform)
{
    if (addTransform)
    {
        transform = addComponent<Transform>();
    }
    m_alive = true;
}

void Entity::begin() {
    if (!m_alive) return;
    for (const auto& component: m_components | std::ranges::views::values) {
        component->onBegin();
    }
}

void Entity::update(float deltaTime)
{
    if (!m_alive) return;
    for (const auto& component: m_components | std::ranges::views::values) {
       component->update(deltaTime);
    }
}

void Entity::destroy()
{
    m_alive = false;
    for (const auto& c: m_components | std::ranges::views::values) {
        c->onDestroy();
    }

    //TODO: Clean class from memory
}

bool Entity::isAlive() const {
    return m_alive;
}




