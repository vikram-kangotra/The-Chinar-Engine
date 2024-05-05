#pragma once

#include <iostream>
#include <string_view>
#include <memory>

#include "component/sprite.h"
#include "coordinator.h"
#include "initializationSystem/spriteLoader.h"
#include "rendererSystem/rendererSystem.h"
#include "rendererSystem/spriteRenderer.h"
#include "signature.h"
#include "component/transform.h"
#include "component/shape.h"
#include "component/color.h"
#include "component/rigidBody.h"
#include "component/size.h"
#include "component/scale.h"
#include "event/eventHandlerSystem.h"
#include "physics/physicsSystem.h"

namespace Chinar {

    class Engine {
        public:
            Engine();

            void createWorld(const int width, const int height, const std::string_view title);

            Coordinator& getCoordinator() { return coordinator; }

            void start();

        private:
            void draw();
            void update();

            void registerSystems();
            void registerComponents();

            template <typename... T>
            Signature makeSignature() {
                Signature signature;
                (signature.set(coordinator.getComponentType<T>()), ...);
                return signature;
            }

        private:
            bool running;
            Window window;

            Coordinator coordinator;

            std::shared_ptr<RendererSystem> rendererSystem;
            std::shared_ptr<SpriteRenderer> spriteRenderer;
            std::shared_ptr<EventHandlerSystem> eventHandlerSystem;
            std::shared_ptr<SpriteLoader> spriteLoader;
            std::shared_ptr<PhysicsSystem> physicsSystem;
    };
}
