#include "Manager.hpp"

void fatalError(std::string errorString) {
    std::cout << "Error: " << errorString << std::endl;
    SDL_Quit();
    exit(1);
}
std::map<std::string, GLTexture, std::less<>> Manager::_textureMap;  // Define it

GLTexture Manager::getTexture(std::string texturePath) {

    // Lookup texture map in map using std::string_view
    auto mit = _textureMap.find(texturePath);

    if (mit == _textureMap.end()) {
        GLTexture newTexture = Manager::IO::loadPNG(texturePath);

        // Construct std::string from std::string_view for map insertion
        _textureMap.emplace(std::string(texturePath), newTexture);

        std::cout << "New Texture Loaded!\n";
        return newTexture;
    }
    std::cout << "Cached Texture Loaded!\n";
    return mit->second;
}

bool Manager::IO::readFileToBuffer(std::string_view filePath, std::vector<unsigned char>& buffer) {
    namespace fs = std::filesystem;

    try {
        if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
            std::cerr << "Error: File does not exist or is not a regular file.\n";
            return false;
        }

        std::size_t fileSize = fs::file_size(filePath);
        buffer.resize(fileSize);

        std::ifstream file(std::string(filePath), std::ios::binary);
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    } catch (const std::exception& e) {
        std::cerr << "File read error: " << e.what() << "\n";
        return false;
    }

    return true;
}

//ImageLoader
GLTexture Manager::IO::loadPNG(std::string_view filePath) {
    GLTexture texture{};
    std::vector<unsigned char> in;
    std::vector<unsigned char> out;

    unsigned long width, height;
    if (readFileToBuffer(filePath, in) == false) {
        fatalError("Failed to Load PNG File to buffer");
    }


    int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
    if (errorCode != 0) {
        fatalError("decodePNG failed with error code " + std::to_string(errorCode));
    }
    glGenTextures(1, &(texture.id));

    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    texture.width = width;
    texture.height = height;

    return texture;

}
void Manager::Inkey::pressKey(uint32_t keyID) {
    _keyMap[keyID] = true;
}

void Manager::Inkey::releaseKey(uint32_t keyID) {
    _keyMap[keyID] = false;
}

bool Manager::Inkey::isKeyPressed(uint32_t keyID) {
    auto it = _keyMap.find(keyID);
    if (it != _keyMap.end()) {
        return it->second;
    }
    return false;
}
float Manager::fps::end() {
        calculateFPS();

    //for fps limiting to _maxFPS
    uint32_t frameTicks = SDL_GetTicks() - _startTicks;
    if (1000.0f / _maxFPS > frameTicks) {
        SDL_Delay(1000.0f / _maxFPS - frameTicks);
    }
    return _fps;
}
void Manager::fps::calculateFPS() {
    static const int NUM_SAMPLES = 20;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static uint32_t prevTicks = SDL_GetTicks();
    uint32_t currentTicks;
    currentTicks = SDL_GetTicks();
    _frameTime = currentTicks - prevTicks;
    prevTicks = currentTicks;

    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    int count;
    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = _maxFPS;
    }
}
