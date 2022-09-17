#include "systemManager.h"

#include <cassert>

namespace Chinar {

    void SystemManager::entityDestroyed(Entity entity) {
        for (auto const& pair: systems) {
            auto const& system = pair.second;
            system->entities.erase(entity);
        }
    }

    void SystemManager::EntitySignatureChanged(Entity entity, Signature signature) {
        for (auto const& pair: systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = signatures[type];
            if ((signature & systemSignature) == systemSignature) {
                system->entities.insert(entity);
            } else {
                system->entities.erase(entity);
            }
        }
    }
}
