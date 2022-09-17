#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace Chinar {

    class Window {
        public:
            void createWindow(int width, int height, const std::string& title, uint32_t flags) {
                this->width = width;
                this->height = height;

                windowHandler = SDL_CreateWindow(title.c_str(),
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        getWidth(), getHeight(),
                        flags);

                if (windowHandler == nullptr) {
                    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window");
                }
            }

            int getWidth() const { return width; }
            int getHeight() const { return height; }

            SDL_Window* getWindowHandler() const { return windowHandler; }

        private:
            int width;
            int height;

            SDL_Window* windowHandler;
    };
}
