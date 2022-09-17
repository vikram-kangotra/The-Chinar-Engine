#pragma once

#include "../window/window.h"
#include "../system/system.h"

namespace Chinar {

    class RendererSystem : public System {
        public:
            void createRenderer(const Window& window, const uint32_t flags);

            SDL_Color hextoRGB(uint32_t hex) const;

            void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
            void setColor(SDL_Color color);
            void clear();
            void present();

            void draw();
        private:

        private:
            SDL_Renderer* rendererHandler;
    };
}
