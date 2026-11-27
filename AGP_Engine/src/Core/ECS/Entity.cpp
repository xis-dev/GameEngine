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
}

void Entity::update(float deltaTime)
{
    for (auto& component: m_components | std::ranges::views::values) {
       component->update(deltaTime);
    }
}

void Entity::destroy()
{
isAlive = false;
    //TODO: Clean class from memory
}




