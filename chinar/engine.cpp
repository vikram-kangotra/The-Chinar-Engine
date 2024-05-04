#include "engine.h"

namespace Chinar {

    Engine::Engine() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize SDL2");
        }

        registerComponents();
        registerSystems();
    }

    void Engine::createWorld(const int width, const int height, const std::string_view title) {
        window.createWindow(width, height, title.data(), SDL_WINDOW_SHOWN);
        rendererSystem->createRenderer(window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        running = true;
    }

    void Engine::registerComponents() {
        coordinator.registerComponent<Chinar::Transform>();
        coordinator.registerComponent<Chinar::Shape>();
        coordinator.registerComponent<Chinar::Size>();
        coordinator.registerComponent<Chinar::Sprite>();
        coordinator.registerComponent<Chinar::Event>();
        coordinator.registerComponent<Chinar::Color>();
        coordinator.registerComponent<Chinar::RigidBody>();
    }

    void Engine::registerSystems() {
        rendererSystem = coordinator.registerSystem<RendererSystem>(); 
        coordinator.setSystemSignature<RendererSystem>(makeSignature<Shape, Color, Transform>());

        spriteRenderer = coordinator.registerSystem<SpriteRenderer>();
        coordinator.setSystemSignature<SpriteRenderer>(makeSignature<Sprite, Size, Transform>());

        eventHandlerSystem = coordinator.registerSystem<EventHandlerSystem>();

        spriteLoader = coordinator.registerSystem<SpriteLoader>();
        coordinator.setSystemSignature<SpriteLoader>(makeSignature<Sprite>());

        physicsSystem = coordinator.registerSystem<PhysicsSystem>();
        coordinator.setSystemSignature<PhysicsSystem>(makeSignature<RigidBody, Transform>());
    }

    void Engine::draw() {
        rendererSystem->setColor(0, 0, 0, 255);
        rendererSystem->clear();

        rendererSystem->draw(coordinator);
        spriteRenderer->draw(coordinator, rendererSystem);

        rendererSystem->present();
    }

    void Engine::update() {
        physicsSystem->update(coordinator);
    }

    void Engine::start() {

        spriteLoader->load(coordinator, rendererSystem);

        while (running) {
            eventHandlerSystem->handle(running);
            draw();
            update();
        }
    }
}
