#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../system/system.h"
#include "../coordinator.h"
#include "../component/sprite.h"
#include "../rendererSystem/rendererSystem.h"

namespace Chinar {

    class SpriteLoader : public System {
        public:
            void load(Coordinator& coordinator, std::shared_ptr<RendererSystem>& renderer) {
                for (auto& entity : entities) {
                    auto& sprite = coordinator.getComponent<Sprite>(entity);
                    sprite.texture = load(renderer->getRendererHandle(), sprite.path);
                }
            }

        private:

            SDL_Texture* load(SDL_Renderer* renderer, const std::string_view path) {

                SDL_Surface* surface = IMG_Load(path.data());

                assert(surface != nullptr && "Surface is nullptr");

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

                assert(texture != nullptr && "Texture is nullptr");

                SDL_FreeSurface(surface);

                return texture;
            }
    };
}
