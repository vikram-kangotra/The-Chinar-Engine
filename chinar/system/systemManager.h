#pragma once

#include <memory>
#include <unordered_map>
#include <cassert>
#include "system.h"
#include "../signature.h"
#include "../entity/entity.h"

namespace Chinar {

    class SystemManager {
        public:
            template <typename T>
            std::shared_ptr<T> registerSystem() {
                const char* typeName = typeid(T).name();
                assert(systems.find(typeName) == systems.end() && "Registering system more than once.");
                auto system = std::make_shared<T>();
                systems.insert({typeName, system});
                return system;
            }

            template <typename T>
            void setSignature(Signature signature) {
                const char* typeName = typeid(T).name();
                assert(systems.find(typeName) != systems.end() && "System used before registered.");
                signatures.insert({typeName, signature});
            }

            void entityDestroyed(Entity entity);

            void EntitySignatureChanged(Entity entity, Signature signature);

        private:
            std::unordered_map<const char*, Signature> signatures{};
            std::unordered_map<const char*, std::shared_ptr<System>> systems{};
    };
}
