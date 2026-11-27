//
// Created by seer on 11/5/26.
//

#include "../../include/AGP_Engine/Core/Level.h"

AGPEngine::Entity * AGPEngine::Level::createEntity(const std::optional<std::string> &name)  {
    m_entities.push_back(std::unique_ptr<Entity>(new Entity()));
    auto* newEnt = m_entities.back().get();
    if (name.has_value()) {
       m_namedEntities.insert({name.value(), newEnt});
    }
    return newEnt;
}

AGPEngine::Entity * AGPEngine::Level::getEntity(const std::string &name) {
    auto entIt = m_namedEntities.find(name);
    if (entIt != m_namedEntities.end()) {
        return entIt->second;
    }

    return nullptr;
}
