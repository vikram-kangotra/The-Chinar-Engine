#pragma once

#include "../component/rigidBody.h"
#include "../system/system.h"
#include "../coordinator.h"

namespace Chinar {

    class PhysicsSystem : public System {
            Vec2<float> center{400, 300};
        public:
            void update(Coordinator& coordinator) {
                for (const auto& entity: entities) {
                    auto& rigidBody = coordinator.getComponent<RigidBody>(entity);
                    auto& transform = coordinator.getComponent<Transform>(entity);

                    rigidBody.acceleration = Vec<float, 2>::normalize(center - transform.pos) * 0.5;

                    rigidBody.velocity += rigidBody.acceleration;
                    transform.pos += rigidBody.velocity;
                }
            }
    };
}
