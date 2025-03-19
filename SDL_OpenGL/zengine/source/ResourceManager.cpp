#include "ResourceManager.hpp"
#include "zengine.hpp"

namespace zengine {

    TextureCache ResourceManager::_textureCache;

    GLTexture ResourceManager::getTexture(std::string texturePath) {

        return _textureCache.getTexture(texturePath);
    }

}
