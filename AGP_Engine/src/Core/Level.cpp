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
    // TODO: Because of the weird state of naming things, its a double find, i will remove this later

    auto entIt = m_namedEntities.find(name);
    if (entIt != m_namedEntities.end()) {
        auto ptrIt = std::ranges::find_if(m_entities, [entIt](const auto& entPtr) {
            return entIt->second == entPtr.get();
        });
        // Was not found in actual entity list, remove from named
        if (ptrIt == m_entities.end()) {
            m_namedEntities.erase(entIt);
            return nullptr;
        }

        return entIt->second;
    }

    return nullptr;
}

void AGPEngine::Level::updateEnd() {
    // TODO: Once entities are ids, either get simply or stage a buffer of entities to be destroyed
    for (const auto& ent: m_entities) {
        if (!ent->isAlive()) {
            m_entitiesToBeDestroyed.push_back(ent.get());
        }
    }

    for (const auto* ent: m_entitiesToBeDestroyed) {
        auto it = std::ranges::find_if(m_entities, [ent](const auto& entPtr) {
            return ent == entPtr.get();
        });
        if (it != m_entities.end()) {
            m_entities.erase(it);
        }
    }

    m_entitiesToBeDestroyed.clear();
}

void AGPEngine::Level::destroyEntity(Entity *entity) {
    if (!entity) return;
    entity->m_alive = false;
    m_entitiesToBeDestroyed.push_back(entity);
}
