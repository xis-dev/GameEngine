#pragma once
#include <concepts>
#include <cstdint>

#include "Core/ECS/Entity.h"
#include "Core/ECS/Entity.h"

// TODO: Actual ECS, using map of components for now
// Specialized template def takes priority
// #define AGP_ENGINE_REGISTER_COMPONENT(x) \
//     namespace AGPEngine { \
//     template<> \
//     class ComponentSubsystem<x> {\
//     static constexpr bool registered = true; } \
// }
//
// namespace AGPEngine {
//     struct Component {
//
//     };
//
//     template<typename C>
//     requires std::derived_from<C, Component>
//     class ComponentSubsystem {
//         static constexpr bool registered = false;
//
//     };
//
//     template <typename C>
//     inline constexpr bool is_registered_component_v = ComponentSubsystem<C>::registered;
// }

namespace AGPEngine {
    class Entity;
    using ComponentID = uint32_t;
    struct Component {


    Entity* owner{nullptr};

        template <typename C>
        requires std::derived_from<C, Component>
        static ComponentID GetID() {
            // Create next id once for each definition
            // TODO: Will likely use bitmasks instead
            static ComponentID outID = nextID++;
            return outID;
        }
        virtual ~Component() = default;

        virtual void onBegin() {}
        virtual void update(float deltaTime) {}
        virtual void onDestroy() {}

    private:
        static ComponentID nextID;
    };

    inline ComponentID Component::nextID = 0;
}


