#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <string_view>
#include <fstream>
#include <filesystem>
#include <cstdint>
#include <cstddef>
#include <random>
#include <utility>
#include <format>
#include <map>
#include <unordered_map>
#include "Vertex.hpp"

extern void fatalError(std::string errorString);

extern int decodePNG(std::vector<unsigned char>& out_image,
                unsigned long& image_width,
                unsigned long& image_height,
                const unsigned char* in_png,
                size_t in_size, bool convert_to_rgba32 = true);

class Manager {

public:
    // SDL inkey process
    struct Inkey {
        void pressKey(uint32_t keyID);
        void releaseKey(uint32_t keyID);
        bool isKeyPressed(uint32_t keyID);
    private:
        std::unordered_map<uint32_t, bool> _keyMap;
    };

    // IO read and decode png
    struct IO {
        static bool readFileToBuffer(std::string_view filePath, std::vector<unsigned char>& buffer);
        //ImageLoader
        static GLTexture loadPNG(std::string_view filePath);
    };
    static GLTexture getTexture(std::string texturePath);
    // FPS Limiter
    struct fps {
        void init(float maxFPS) { _maxFPS = maxFPS; }
        void begin() { _startTicks = SDL_GetTicks(); }
        float end();
    private:
        void calculateFPS();
        float _maxFPS;
        uint32_t _startTicks;
        float _fps;
        float _frameTime;
    };

private:

    static std::map<std::string, GLTexture, std::less<>> _textureMap;
};


#endif //MANAGER_HPP
