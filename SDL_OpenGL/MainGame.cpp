#include "MainGame.h"
#include <iostream>
#include <string>

void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit...";
    int tmp;
    std::cin >> tmp;
    SDL_Quit();
}
MainGame::MainGame()
{
    //Constructor
    _window = nullptr;
    _screenWidth = 800; //1024;
    _screenHeight = 800; //768;
    _gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
    //Destructor
    //Close and destroy the window
    SDL_DestroyWindow( _window );

    //Clean up
    SDL_Quit();
}

void MainGame::run() {
    initSystems();
    _sprite.init(100, 100, 80, 80, 5);

    _sprite.init(150, 150, 50, 50, 7);
    gameLoop();

}

void MainGame::initSystems() {
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow("Graphics Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window Could Not Be Created!");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        fatalError("SDL_GL Context Could Not Be Created!");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could Not Initialize glew!");
    }
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glClearColor(0.0f, 0.5f, 0.0f, 1.0f);

    GLint matrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
    SDL_Log("Current GL_MATRIX_MODE: %d", matrixMode);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, _screenWidth, _screenHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
    SDL_Log("Current GL_MATRIX_MODE: %d", matrixMode);

}

void MainGame::processInput() {
    SDL_Event evnt;
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                SDL_Log("We got a motion event.");
                SDL_Log("Current mouse position is: (%d, %d)", evnt.motion.x, evnt.motion.y);
                break;
            default:
                SDL_Log("Unhandled Event!");
                break;
        }
    }
}
void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _sprite.draw();

    SDL_GL_SwapWindow(_window);
}

void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        processInput();
        drawGame();
    }
}

