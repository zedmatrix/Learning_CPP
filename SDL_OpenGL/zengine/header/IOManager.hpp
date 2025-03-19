#ifndef IOMANAGER_HPP
#define IOMANAGER_HPP

#include "zengine.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <string_view>

namespace zengine {

    class IOManager {

    public:
        static bool readFileToBuffer(std::string_view filePath, std::vector<unsigned char>& buffer);

        //ImageLoader
        static GLTexture loadPNG(std::string_view filePath);
    };
}

#endif //IOMANAGER_HPP
