#pragma once

#include "../system/system.h"
#include "../coordinator.h"
#include "../component/event.h"
#include <SDL2/SDL.h>

namespace Chinar {

    class EventHandlerSystem : public System {
        public:
            void handle(bool& running) {
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT: running = false; break;
                    }
                }

                for (const auto& entity : entities) {
                    // auto& event = Coordinator::getCoordinator().getComponent<Chinar::Event>(entity);
                    // event.event = this->event;
                }
            }

        private:
            SDL_Event event;
    };
}
