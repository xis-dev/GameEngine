#pragma once

#include "Components/Component.h"
#include "Components/Transform.h"

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
        virtual ~Entity() = default;

        Transform* transform{nullptr};






        template <typename C, typename... Args>
        requires std::derived_from<C, Component> &&
            std::is_constructible_v<C, Args...>
        C* addComponent(Args&&... args) {

            // Let it override last component but issue warning
            if (m_components.contains(Component::GetID<C>())) {
                std::cerr << "AGP_ENGINE::ENTITY: Warning: Overriding already existing component with this definition. Duplicate Component?\n";
            }
            //Split the Component setup. I feel it works the same way, but is more readable
            auto component = std::make_unique<C>(std::forward<Args>(args)...);
            C* out = component.get();
            out->owner = this;

            m_components[Component::GetID<C>()] = std::move(component);
            return out;
        }





        template <typename C>
        requires std::derived_from<C, Component>
        const C* getComponent() const {
            if (!m_components.contains(Component::GetID<C>())) return nullptr;

            auto it = m_components.find(Component::GetID<C>());
            if (it == m_components.end()) return nullptr;

            return static_cast<const C*>(it->second.get());
        }





        template <typename C>
        requires std::derived_from<C, Component>
        C* getComponent() {
            if (!m_components.contains(Component::GetID<C>())) return nullptr;

            return m_components[Component::GetID<C>()].get();
        }





        template <typename C>
        requires std::derived_from<C, Component>
        bool hasComponent() const {
            return m_components.contains(Component::GetID<C>());
        }




        virtual void begin();
        virtual void update(float deltaTime);
        virtual void destroy();

        bool isAlive() const;

    private:
        // Temporary unordered map, just want this up for SpriteRenderer component to be started
        std::unordered_map<ComponentID, std::unique_ptr<Component>> m_components{};

        bool m_alive{};
        bool m_toBeDestroyed{};

    };

}
