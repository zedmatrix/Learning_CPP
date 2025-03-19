#include "zengine.hpp"

namespace zengine {

    int init() {
        // Initialize Everything and Set Up Double Buffering
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        return 0;
    }
}
