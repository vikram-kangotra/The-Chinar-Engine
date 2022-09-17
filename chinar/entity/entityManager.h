#pragma once

#include <queue>
#include <array>
#include "entity.h"
#include "../signature.h"

namespace Chinar {

    class EntityManager {
        public:
            EntityManager() {}

            Entity createEntity();
            void destroyEntity(Entity entity);

            void setSignature(Entity entity, Signature signature);
            Signature getSignature(Entity entity);

        private:
            std::queue<Entity> availableEntities;
            std::array<Signature, MAX_ENTITIES> signatures;
            uint32_t spawnCount{};
            uint32_t livingEntityCount{};
    };
}
