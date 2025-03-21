#ifndef MAINGAME_HPP
#define MAINGAME_HPP
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <memory>
#include "Window.hpp"
#include "Sprite.hpp"
#include "Camera.hpp"
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
    void calculateFPS();

    Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    float _time;
    float _maxFPS;

    float _fps;
    float _frameTime;
    Camera _camera;

    Sprite _sprites;
    GLSLProgram _colorProgram;

};

#endif //MAINGAME_HPP
