#ifndef MAINGAME_HPP
#define MAINGAME_HPP
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <string>
#include <format>

#include "Sprite.hpp"
#include "Error.hpp"
#include "GLSLProgram.hpp"


enum class GameState {PLAY, EXIT};

class MainGame {

public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();

    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    float _time;

    std::vector <Sprite*> _sprites;
    GLSLProgram _colorProgram;



};

#endif //MAINGAME_HPP
