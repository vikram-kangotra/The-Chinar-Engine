#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

namespace Chinar {

    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        SDL_Color getColor() {
            return {r, g, b, a};
        }
    };
}
