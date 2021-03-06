#pragma once

namespace Chinar {

    class AIState {
        public:
            AIState(class AIComponent* owner)
            : mOwner{owner} {}

            virtual void update(const float deltaTime) = 0;
            virtual void onEnter() = 0;
            virtual void onExit() = 0;

            virtual const char* getName() const = 0;
        protected:

            class AIComponent* mOwner;
    };
}
