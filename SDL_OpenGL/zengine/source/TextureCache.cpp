#include "TextureCache.hpp"
#include "IOManager.hpp"
#include <utility>
#include <iostream>
#include "zengine.hpp"

namespace zengine {

    TextureCache::TextureCache() {

    }

    TextureCache::~TextureCache() {

    }

    GLTexture TextureCache::getTexture(std::string_view texturePath) {

    // Lookup texture map in map using std::string_view
    auto mit = _textureMap.find(texturePath);

    if (mit == _textureMap.end()) {
        GLTexture newTexture = IOManager::loadPNG(texturePath);

        // Construct std::string from std::string_view for map insertion
        _textureMap.emplace(std::string(texturePath), newTexture);

        std::cout << "New Texture Loaded!\n";
        return newTexture;
    }
    std::cout << "Cached Texture Loaded!\n";
    return mit->second;
}

}
