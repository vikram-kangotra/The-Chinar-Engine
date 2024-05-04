#pragma once

#include "../window/window.h"
#include "../system/system.h"
#include "../coordinator.h"
#include "rendererSystem.h"

namespace Chinar {

    class SpriteRenderer : public System {
        public:
            void draw(Coordinator& coordinator, std::shared_ptr<RendererSystem>& renderer);
    };
}
