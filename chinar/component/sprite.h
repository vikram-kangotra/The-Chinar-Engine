#pragma once

#include <string>
#include <string_view>
#include <SDL2/SDL.h>

namespace Chinar {

    struct Sprite {
        std::string path;
        SDL_Texture* texture = nullptr;
    };
}
