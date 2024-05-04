#include "engine.h"

using namespace Chinar;

int main() {

    Engine::init();
    Engine::createWorld(800, 600, "The Game");

    Entity entity = Coordinator::getCoordinator().createEntity();
    Coordinator::getCoordinator().addComponent(entity, Shape{100, 100});
    Coordinator::getCoordinator().addComponent(entity, Color{255, 0, 0, 255});
    Coordinator::getCoordinator().addComponent(entity, Transform{{100, 400}});
    Coordinator::getCoordinator().addComponent(entity, RigidBody{{6, 0}, {0, 0}});

    Entity entity2 = Coordinator::getCoordinator().createEntity();
    Coordinator::getCoordinator().addComponent(entity2, Shape{80, 80});
    Coordinator::getCoordinator().addComponent(entity2, Color{24, 255, 0, 255});
    Coordinator::getCoordinator().addComponent(entity2, Transform{{100, 100}});
    Coordinator::getCoordinator().addComponent(entity2, RigidBody{{1, 1},{0, 0}});

    Entity entity1 = Coordinator::getCoordinator().createEntity();
    Coordinator::getCoordinator().addComponent(entity1, Shape{120, 80});
    Coordinator::getCoordinator().addComponent(entity1, Color{24, 134, 253, 255});
    Coordinator::getCoordinator().addComponent(entity1, Transform{{50, 50}});
    Coordinator::getCoordinator().addComponent(entity1, RigidBody{{5, 3},{0, 0}});

    Engine::start();

    return 0;
}
