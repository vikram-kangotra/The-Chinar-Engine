#include "rendererSystem.h"
#include "../coordinator.h"
#include "../component/shape.h"
#include "../component/color.h"
#include "../component/transform.h"
#include "../component/sprite.h"
#include "../component/size.h"
#include "spriteRenderer.h"

namespace Chinar {

    void SpriteRenderer::draw(Coordinator& coordinator, std::shared_ptr<RendererSystem>& renderer) {
        for (const auto& entity : entities) {
            auto& transform = coordinator.getComponent<Chinar::Transform>(entity);
            auto& size = coordinator.getComponent<Chinar::Size>(entity);
            auto& sprite = coordinator.getComponent<Chinar::Sprite>(entity);

            SDL_Rect rect = {static_cast<int>(transform.pos.x), static_cast<int>(transform.pos.y), size.width, size.height};

            SDL_RenderCopy(renderer->getRendererHandle(), sprite.texture, nullptr, &rect);

            SDL_RenderDrawRect(renderer->getRendererHandle(), &rect);
        }
    }
}
