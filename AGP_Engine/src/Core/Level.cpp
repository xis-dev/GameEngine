//
// Created by seer on 11/5/26.
//

#include "../../include/AGP_Engine/Core/Level.h"

AGPEngine::Entity * AGPEngine::Level::createEntity()  {
    m_entities.push_back(std::unique_ptr<Entity>(new Entity()));
    return m_entities.back().get();
}
