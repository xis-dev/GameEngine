//
// Created by seer on 11/25/26.
//

#include "Entity.h"

AGPEngine::Entity::Entity(bool addTransform) {
    if (addTransform) {
        m_transform = addComponent<Transform>();
    }
}
