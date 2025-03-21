#include "MainGame.hpp"

MainGame::MainGame () :
    _screenWidth(800),
    _screenHeight(600),
    _gameState(GameState::PLAY),
    _time(0.0f),
    _maxFPS(60.0f) {

    _camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame () {
}

void MainGame::run() {
    initSystems();

    gameLoop();

}

void MainGame::initSystems() {
    // Initialize Everything and Set Up Double Buffering
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    _window.create("Game Engine", _screenWidth, _screenHeight, 0);

    initShaders();
    _sprites.init();
    _fpsLimiter.init(_maxFPS);
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
        _fpsLimiter.begin();

        processInput();
        _time += 0.01;
        _camera.update();
        drawGame();

        _fps = _fpsLimiter.end();
        frameCount++;
        if (frameCount > 10) {
            std::cout << std::format("Frames per Second: {} FPS\n", _fps);
            frameCount = 0;
        }
    }
}

void MainGame::processInput() {

    SDL_Event _event;
    const float CAMERA_SPEED = 0.5f;
    const float SCALE_SPEED = 0.1f;

    while (SDL_PollEvent(&_event)) {
        switch (_event.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            // case SDL_MOUSEMOTION:
            //     std::cout << std::format("Mouse({},{})\n", _event.motion.y, _event.motion.x);
            //     break;

            case SDL_KEYDOWN:
                _inkey.pressKey(_event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inkey.releaseKey(_event.key.keysym.sym);
                break;
        }
    }
    if (_inkey.isKeyPressed(SDLK_UP)) _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    if (_inkey.isKeyPressed(SDLK_DOWN)) _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
    if (_inkey.isKeyPressed(SDLK_RIGHT))_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    if (_inkey.isKeyPressed(SDLK_LEFT)) _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    if (_inkey.isKeyPressed(SDLK_z)) _camera.setScale(_camera.getScale() + SCALE_SPEED);
    if (_inkey.isKeyPressed(SDLK_x)) _camera.setScale(_camera.getScale() - SCALE_SPEED);


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

    //Set the camera matrix
    GLuint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

    //Sprite Batch
    _sprites.begin();
    glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static GLTexture texture = Manager::getTexture("Textures/myCharacter_standing.png");
    Color color{128, 128, 128, 255};

    _sprites.draw(pos, uv, texture.id, 0.0f, color);
    _sprites.end();
    _sprites.renderBatch();

    // unbind Texture
    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();
    _window.swapBuffer();

}
