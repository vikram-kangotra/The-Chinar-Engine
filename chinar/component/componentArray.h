#pragma once

#include <iostream>
#include <array>
#include <unordered_map>
#include <cstddef>
#include <cassert>
#include "../entity/entity.h"

namespace Chinar {

    class IComponentArray {
        public:
            virtual ~IComponentArray() = default;
            virtual void entityDestroyed(Entity entity) = 0;
    };

    template <typename T>
    class ComponentArray : public IComponentArray {
        public:
            void insertData(Entity entity, T component) {
                assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");
                size_t newIndex = size;
                entityToIndexMap[entity] = newIndex;
                indexToEntityMap[newIndex] = entity;
                componentArray[newIndex] = component;
                ++size;
            }

            void removeData(Entity entity) {
                assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");

                size_t indexOfRemovedEntity = entityToIndexMap[entity];
                size_t indexOfLastElement = size - 1;

                componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];
                Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
                entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
                indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
                entityToIndexMap.erase(entity);
                indexToEntityMap.erase(indexOfLastElement);

                --size;
            }

            T& getData(Entity entity) {
                assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");
                return componentArray[entityToIndexMap[entity]];
            }

            void entityDestroyed(Entity entity) {
                if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
                    removeData(entity);
                }
            }


        private:
            std::array<T, MAX_ENTITIES> componentArray;
            std::unordered_map<Entity, size_t> entityToIndexMap;
            std::unordered_map<size_t, Entity> indexToEntityMap;
            size_t size;
    };
}
