#pragma once

#include <memory>

#include "Window.h"
#include "ECS/Entity.h"

#include <vector>

namespace AGPEngine {

    class Level {

    public:
        Level() = default;
        Level(const Level&) = delete;
        Level& operator=(const Level&) = delete;

        Level(Level&& l) noexcept = default;
        Level& operator=(Level&& l) noexcept = default;

        Entity* createEntity();
    private:
        std::vector<std::unique_ptr<Entity>> m_entities{};
    };
}
