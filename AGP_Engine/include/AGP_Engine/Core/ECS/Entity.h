#pragma once

#include "Components/Component.h"
#include "Components/TransformComponent.h"

#include <iostream>
#include <unordered_map>
#include <forward_list>
#include <memory>
namespace AGPEngine {

    class Level;

    class Entity {
        // Friend Level so it can access the constructor
        friend Level;

    private:
        // Private constructor, only level should be able to create entities
        explicit Entity(bool addTransform = true);

    public:

        template <typename C, typename... Args>
        requires std::derived_from<C, Component> &&
            std::is_constructible_v<C, Args...>
        C* addComponent(Args&&... args) {

            // Let it override last component but issue warning
            if (m_components.contains(Component::GetID<C>())) {
                std::cout << "AGP_ENGINE::ENTITY: Warning: Overriding already existing component with this definition.\n";
            }
            m_components[Component::GetID<C>()] = C(std::forward<Args>(args)...);
            return dynamic_cast<C*>(&m_components[Component::GetID<C>()]);
        }

        template <typename C>
        requires std::derived_from<C, Component>
        const C* getComponent() const{
            if (!m_components.contains(Component::GetID<C>())) return nullptr;

            return &m_components[Component::GetID<C>()];
        }

        template <typename C>
        requires std::derived_from<C, Component>
        C* getComponent() {
            if (!m_components.contains(Component::GetID<C>())) return nullptr;

            return &m_components[Component::GetID<C>()];
        }

        template <typename C>
        requires std::derived_from<C, Component>
        bool hasComponent() const {
            return m_components.contains(Component::GetID<C>());
        }

    private:
        // Temporary unordered map, just want this up for SpriteRenderer component to be started
        std::unordered_map<ComponentID, Component> m_components{};

        Transform* m_transform{nullptr};
    };

}
