#include "MainGame.hpp"
#include "IOManager.hpp"

MainGame::MainGame () :
    _window(nullptr),
    _screenWidth(640),
    _screenHeight(480),
    _gameState(GameState::PLAY),
    _time(0.0f) {

}

MainGame::~MainGame () {

}

void MainGame::run() {
    initSystems();

    _sprites.push_back(new Sprite());
    _sprites.back()->init(-0.5f, 0.5f, 0.5f, 0.5f, "src/Textures/block_grid.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->init(-0.2f, -0.2f, 0.6f, 0.6f, "src/Textures/PNG/CharacterRight_Standing.png");

    _sprites.push_back(new Sprite());
    _sprites.back()->init(0.2f, -1.2f, 0.6f, 0.6f, "src/Textures/PNG/CharacterRight_Standing.png");
    //_playerTexture = IOManager::loadPNG("src/Textures/PNG/CharacterRight_Standing.png");
    //_playerTexture = IOManager::loadPNG("src/Textures/block_grid.png");

    gameLoop();

}

void MainGame::initSystems() {

    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("SDL OpenGL Demo",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               _screenWidth,
                               _screenHeight,
                               SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL_GL Context could not be initialized");
    }
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not Initialize GLEW");
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    initShaders();
}
void MainGame::initShaders() {
    _colorProgram.compileShaders("src/Shaders/VertexShader", "src/Shaders/FragmentShader");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();

}

void MainGame::gameLoop() {

    while (_gameState != GameState::EXIT) {
        processInput();
        _time += 0.01;
        drawGame();
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

    SDL_GL_SwapWindow(_window);

}






