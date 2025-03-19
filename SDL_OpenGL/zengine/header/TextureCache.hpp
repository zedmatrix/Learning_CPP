#ifndef TEXTURECACHE_HPP
#define TEXTURECACHE_HPP
#include <map>
#include <string>
#include "GLTexture.hpp"

namespace zengine {

    class TextureCache {

    public:
        TextureCache();
        ~TextureCache();

        GLTexture getTexture(std::string_view texturePath);

    private:
        std::map<std::string, GLTexture, std::less<>> _textureMap;

    };
}


#endif //TEXTURECACHE_HPP
