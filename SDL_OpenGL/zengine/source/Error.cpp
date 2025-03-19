#include <SDL2/SDL.h>
#include "Error.hpp"
#include "zengine.hpp"

namespace zengine {

    void fatalError(std::string errorString) {
        std::cout << "Error: " << errorString << std::endl;
        SDL_Quit();
        exit(1);
    }

}
