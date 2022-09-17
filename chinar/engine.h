#pragma once

#include <iostream>

#include <memory>
#include "coordinator.h"
#include "signature.h"
#include "component/transform.h"
#include "component/shape.h"
#include "component/color.h"
#include "component/rigidBody.h"
#include "rendererSystem/rendererSystem.h"
#include "event/eventHandlerSystem.h"
#include "physics/physicsSystem.h"

namespace Chinar {
    namespace Engine {

        namespace {
            bool running;
            Window window;
        }

        namespace {
            std::shared_ptr<RendererSystem> rendererSystem;
            std::shared_ptr<EventHandlerSystem> eventHandlerSystem;
            std::shared_ptr<PhysicsSystem> physicsSystem;
        }

        namespace {
            void registerComponents() {
                Chinar::Coordinator::getCoordinator().registerComponent<Chinar::Transform>();
                Chinar::Coordinator::getCoordinator().registerComponent<Chinar::Shape>();
                Chinar::Coordinator::getCoordinator().registerComponent<Chinar::Event>();
                Chinar::Coordinator::getCoordinator().registerComponent<Chinar::Color>();
                Chinar::Coordinator::getCoordinator().registerComponent<Chinar::RigidBody>();
            }

            template <typename... T>
            Signature makeSignature() {
                Signature signature;
                (signature.set(Chinar::Coordinator::getCoordinator().getComponentType<T>()), ...);
                return signature;
            }

            void registerSystems() {
                rendererSystem = Chinar::Coordinator::getCoordinator().registerSystem<RendererSystem>(); 
                Chinar::Coordinator::getCoordinator().setSystemSignature<RendererSystem>(makeSignature<Shape, Color, Transform>());

                eventHandlerSystem = Chinar::Coordinator::getCoordinator().registerSystem<EventHandlerSystem>();

                physicsSystem = Chinar::Coordinator::getCoordinator().registerSystem<PhysicsSystem>();
                Chinar::Coordinator::getCoordinator().setSystemSignature<PhysicsSystem>(makeSignature<RigidBody, Transform>());
            }
        }

        void init() {
            if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
                SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize SDL2");
            }

            registerComponents();
            registerSystems();
        }

        void createWorld(const int width, const int height, const std::string& title) {
            window.createWindow(width, height, title, SDL_WINDOW_SHOWN);
            rendererSystem->createRenderer(window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            running = true;
        }

        void draw() {
            rendererSystem->setColor(255, 127, 63, 255);
            rendererSystem->clear();

            rendererSystem->draw(); 

            rendererSystem->present();
        }

        void update() {
            physicsSystem->update();
        }

        void start() {
            while (running) {
                eventHandlerSystem->handle(running);
                draw();
                update();
            }
        }
    }
}
