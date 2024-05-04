#include "engine.h"

using namespace Chinar;

int main() {

    Engine engine;
    engine.createWorld(800, 600, "The Game");

    auto& coordinator = engine.getCoordinator();

    Entity entity = coordinator.createEntity();
    coordinator.addComponent(entity, Shape{100, 100});
    coordinator.addComponent(entity, Color{255, 0, 0, 255});
    coordinator.addComponent(entity, Transform{{100, 400}});
    coordinator.addComponent(entity, RigidBody{{6, 0}, {0, 0}});

    Entity entity2 = coordinator.createEntity();
    coordinator.addComponent(entity2, Shape{80, 80});
    coordinator.addComponent(entity2, Color{24, 255, 0, 255});
    coordinator.addComponent(entity2, Transform{{100, 100}});
    coordinator.addComponent(entity2, RigidBody{{1, 1},{0, 0}});

    Entity entity1 = coordinator.createEntity();
    coordinator.addComponent(entity1, Shape{120, 80});
    coordinator.addComponent(entity1, Color{24, 134, 253, 255});
    coordinator.addComponent(entity1, Transform{{50, 50}});
    coordinator.addComponent(entity1, RigidBody{{5, 3},{0, 0}});

    engine.start();

    return 0;
}
