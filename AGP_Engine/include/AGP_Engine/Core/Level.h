#pragma once

#include <memory>

#include "Window.h"
#include "ECS/Entity.h"

#include <vector>

namespace AGPEngine {

    class Level {

    public:
        Entity* createEntity();
    private:
        std::vector<std::unique_ptr<Entity>> m_entities{};
    };
}
