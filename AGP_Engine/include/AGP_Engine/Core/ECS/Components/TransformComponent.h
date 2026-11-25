#pragma once

#include "Component.h"
#include "glm/vec3.hpp"
#include "glm/detail/type_quat.hpp"

namespace AGPEngine {

    struct Transform: public Component{

        glm::vec3 position{};
        glm::vec3 scale{};
    };
}
