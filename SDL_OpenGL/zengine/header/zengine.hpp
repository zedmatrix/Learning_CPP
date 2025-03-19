#ifndef ZENGINE_HPP
#define ZENGINE_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Error.hpp"
#include "GLSLProgram.hpp"
#include "GLTexture.hpp"
#include "IOManager.hpp"
#include "picopng.hpp"
#include "ResourceManager.hpp"
#include "Sprite.hpp"
#include "TextureCache.hpp"
#include "Vertex.hpp"
#include "Window.hpp"

namespace zengine {

    extern int init();

}

#endif //ZENGINE_HPP
