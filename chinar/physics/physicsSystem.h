#pragma once

#include "../component/rigidBody.h"
#include "../system/system.h"
#include "../coordinator.h"

namespace Chinar {

    class PhysicsSystem : public System {
            Vec2<float> center{400, 300};
        public:
            void update() {
                for (const auto& entity: entities) {
                    auto& rigidBody = Coordinator::getCoordinator().getComponent<RigidBody>(entity);
                    auto& transform = Coordinator::getCoordinator().getComponent<Transform>(entity);

                    rigidBody.acceleration = Vec<float, 2>::normalize(center - transform.pos) * 0.5;

                    rigidBody.velocity += rigidBody.acceleration;
                    transform.pos += rigidBody.velocity;
                }
            }
    };
}
