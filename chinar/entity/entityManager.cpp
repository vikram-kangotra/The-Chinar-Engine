#include "entityManager.h"
#include <cassert>

namespace Chinar {

    Entity EntityManager::createEntity() {
        assert(livingEntityCount < MAX_ENTITIES && 
                "Too many entities in existence.");
        Entity id = spawnCount++;
        if (id > MAX_ENTITIES) {
            id = availableEntities.front();
            availableEntities.pop();
        }
        ++livingEntityCount;
        return id;
    }

    void EntityManager::destroyEntity(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        signatures[entity].reset();
        availableEntities.push(entity);
        --livingEntityCount;
    }

    void EntityManager::setSignature(Entity entity, Signature signature) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        signatures[entity] = signature;
    }

    Signature EntityManager::getSignature(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        return signatures[entity];
    }
}
