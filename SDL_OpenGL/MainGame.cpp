#include "MainGame.hpp"

using namespace zengine;

MainGame::MainGame () :
    _screenWidth(800),
    _screenHeight(600),
    _gameState(GameState::PLAY),
    _time(0.0f),
    _maxFPS(60.0f) {

}

MainGame::~MainGame () {

}

void MainGame::run() {
    initSystems();

    _sprites.push_back(new Sprite());
    _sprites.back()->init(-0.5f, 0.5f, 0.5f, 0.5f, "Textures/block_grid.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->init(-0.2f, -0.2f, 0.6f, 0.6f, "Textures/CharacterRight_Standing.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->init(0.2f, -1.2f, 0.6f, 0.6f, "Textures/CharacterRight_Standing.png");
    //_playerTexture = IOManager::loadPNG("src/Textures/PNG/CharacterRight_Standing.png");
    //_playerTexture = IOManager::loadPNG("src/Textures/block_grid.png");

    gameLoop();

}

void MainGame::initSystems() {
    init();
    _window.create("Game Engine", _screenWidth, _screenHeight, 0);

    initShaders();
}
void MainGame::initShaders() {
    _colorProgram.compileShaders("Shaders/VertexShader", "Shaders/FragmentShader");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();

}

void MainGame::gameLoop() {

    static int frameCount = 0;
    while (_gameState != GameState::EXIT) {
        float startTicks = SDL_GetTicks();

        processInput();
        _time += 0.01;
        drawGame();

        calculateFPS();
        frameCount++;
        if (frameCount > 10) {
            std::cout << std::format("Frames per Second: {} FPS\n", _fps);
            frameCount = 0;
        }

        //for fps limiting to _maxFPS
        float frameTicks = SDL_GetTicks() - startTicks;
        if (1000.0f / _maxFPS > frameTicks) {
            SDL_Delay(1000.0f / _maxFPS - frameTicks);
        }
    }

}
void MainGame::processInput() {

    SDL_Event _event;

    while (SDL_PollEvent(&_event)) {
        switch (_event.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            // case SDL_MOUSEMOTION:
            //     std::cout << std::format("Mouse({},{})\n", _event.motion.y, _event.motion.x);
            //     break;
            // case SDL_MOUSEWHEEL:
            //     std::cout << std::format("Mouse({},{})\n", _event.wheel.y, _event.wheel.x);
            //     break;
            // default:
            //     SDL_Log("Unhandled Event!");
            //     break;
        }
    }
}
void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    // binding textures
    glActiveTexture(GL_TEXTURE0);

    GLuint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    //binding time motion
    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);

    for (size_t i = 0; i < _sprites.size(); i++) {
        _sprites[i]->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();

    _window.swapBuffer();

}
void MainGame::calculateFPS() {
    static const int NUM_SAMPLES = 20;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static float prevTicks = SDL_GetTicks();
    float currentTicks;
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
        _fps = 60.0f;
    }
}





