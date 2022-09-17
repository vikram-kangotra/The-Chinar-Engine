#pragma once

#include <memory>
#include "component/componentManager.h"
#include "entity/entityManager.h"
#include "system/systemManager.h"

namespace Chinar {

    class Coordinator {
        public:
            static Coordinator& getCoordinator() {
                static Coordinator coordinator;
                return coordinator;
            }

            Entity createEntity() {
                return entityManager->createEntity();
            }

            void destroyEntity(Entity entity) {
                entityManager->destroyEntity(entity);
                componentManager->entityDestroyed(entity);
                systemManager->entityDestroyed(entity);
            }

            template <typename T>
            void registerComponent() {
                componentManager->registerComponent<T>();
            }

            template <typename T>
            void addComponent(Entity entity, T component) {
                componentManager->addComponent(entity, component);
                auto signature = entityManager->getSignature(entity);
                signature.set(componentManager->getComponentType<T>(), true);
                entityManager->setSignature(entity, signature);
                systemManager->EntitySignatureChanged(entity, signature);
            }

            template <typename T>
            void removeComponent(Entity entity) {
                componentManager->removeComponent<T>(entity);
                auto signature = entityManager->getSignature(entity);
                signature.set(componentManager->getComponent<T>(entity));
                entityManager->setSignature(entity, signature);
                systemManager->EntitySignatureChanged(entity, signature);
            }

            template <typename T>
            T& getComponent(Entity entity) {
                return componentManager->getComponent<T>(entity);
            }

            template <typename T>
            ComponentType getComponentType() {
                return componentManager->getComponentType<T>();
            }

            template <typename T>
            std::shared_ptr<T> registerSystem() {
                return systemManager->registerSystem<T>();
            }

            template <typename T>
            void setSystemSignature(Signature signature) {
                systemManager->setSignature<T>(signature);
            }

        protected:
            Coordinator() {
                componentManager = std::make_unique<ComponentManager>();
                entityManager = std::make_unique<EntityManager>();
                systemManager = std::make_unique<SystemManager>();
            }

        private:
            std::unique_ptr<ComponentManager> componentManager;
            std::unique_ptr<EntityManager> entityManager;
            std::unique_ptr<SystemManager> systemManager;
    };
}
