#pragma once
#include <string>
#include <vector>
#include "GLTexture.hpp"

class IOManager {

public:
    static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
    static bool readFileToBuffer(std::string filePath, std::string& buffer);

    //ImageLoader
    static GLTexture loadPNG(std::string filePath);
};
