//
// Created by seer on 11/25/26.
//

#include "Entity.h"

using namespace AGPEngine;
static bool isAlive = true;


Entity::Entity(bool addTransform)
{
    if (addTransform)
    {
        transform = addComponent<Transform>();
    }
}

void Entity::update(float deltaTime)
{
    while (isAlive)
    {


    };
}

void Entity::destory()
{
isAlive = false;
    //TODO: Clean class from memory
}




