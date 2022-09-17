#pragma once

#include "../entity/entity.h"
#include <set>

namespace Chinar {

    class System {
        public:
            std::set<Entity> entities;
    };
}
