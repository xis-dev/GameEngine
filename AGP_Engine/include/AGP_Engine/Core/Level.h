#pragma once

#include <memory>

#include "Window.h"
#include "ECS/Entity.h"

#include <vector>

namespace AGPEngine {

    class Level {

    public:
        virtual ~Level() = default;

        Level() = default;
        Level(const Level&) = delete;
        Level& operator=(const Level&) = delete;

        Level(Level&& l) noexcept = default;
        Level& operator=(Level&& l) noexcept = default;

        Entity* createEntity(const std::optional<std::string>& name = {});
        Entity* getEntity(const std::string& name);

        const std::vector<std::unique_ptr<Entity>>& getEntities() const {return m_entities;}

        // TODO: Gets changed to delegate
        virtual void onBegin() {
            for (const auto& entity: m_entities) {
                entity->begin();
            }
        }
        virtual void update(float deltaTime) {
            for (const auto& ent: m_entities) {
                ent->update(deltaTime);
            }
        }
    private:
        std::vector<std::unique_ptr<Entity>> m_entities{};
        std::unordered_map<std::string, Entity*> m_namedEntities{};
    };
}
