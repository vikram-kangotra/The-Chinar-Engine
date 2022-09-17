#include "rendererSystem.h"
#include "../coordinator.h"
#include "../component/shape.h"
#include "../component/color.h"
#include "../component/transform.h"

namespace Chinar {

    void RendererSystem::createRenderer(const Window& window, const uint32_t flags) {
        rendererHandler = SDL_CreateRenderer(window.getWindowHandler(), -1, flags); 
        if (rendererHandler == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create RendererSystem");
        }
    }   

    SDL_Color RendererSystem::hextoRGB(uint32_t hex) const {
        SDL_Color color;
        color.r = (hex >> 24) & 0xff;
        color.g = (hex >> 16) & 0xff;
        color.b = (hex >> 8) & 0xff;
        color.a = (hex >> 0) & 0xff;
        return color;
    }

    void RendererSystem::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SDL_SetRenderDrawColor(rendererHandler, r, g, b, a);
    }

    void RendererSystem::setColor(SDL_Color color) {
        setColor(color.r, color.g, color.b, color.a); 
    }

    void RendererSystem::clear() {
        SDL_RenderClear(rendererHandler);
    }

    void RendererSystem::present() {
        SDL_RenderPresent(rendererHandler);
    }

    void RendererSystem::draw() {
        for (const auto& entity : entities) {
            auto& shape = Coordinator::getCoordinator().getComponent<Chinar::Shape>(entity);
            auto& transform = Coordinator::getCoordinator().getComponent<Chinar::Transform>(entity);
            auto& color = Coordinator::getCoordinator().getComponent<Chinar::Color>(entity);

            setColor(color.getColor());

            SDL_Rect rect = {static_cast<int>(transform.pos.x), static_cast<int>(transform.pos.y), shape.width, shape.height};
            SDL_RenderFillRect(rendererHandler, &rect);
        }
    }
}
