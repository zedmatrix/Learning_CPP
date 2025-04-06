#pragma once
#include "IMainGame.hpp"
#include "IMainWindow.hpp"
#include "IGameScreen.hpp"
#include <box2d/box2d.h>
#include "Box2d.hpp"
#include <vector>
#include "GLTexture.hpp"
#include "SpriteBatch.hpp"
#include "Camera.hpp"
#include "GLSLProgram.hpp"

class GameScreens : public IGameScreen {

public:
    GameScreens(IMainWindow* window);
    virtual void build() override;
    virtual void destroy() override;

    // Called when a screen enters and exits focus
    virtual void onEntry() override;
    virtual void onExit() override;

    // Called in the maingame loop
    virtual void update() override;
    virtual void draw() override;

    virtual int getNextScreenIndex() const override;
    virtual int getPreviousScreenIndex() const override;
private:
    void checkInput();
    IMainWindow* m_window;
    SpriteBatch m_spriteBatch;
    GLSLProgram m_textureProgram;
    Camera m_camera;
    GLTexture m_texture;
    std::vector<Box> m_boxes;
    std::unique_ptr<b2World> m_world;

};

class App : public IMainGame {

public:
    App();

    void onInit() override;
    void addScreens() override;
    void onExit() override;


private:
    std::shared_ptr<GameScreens> m_gameScreens; /* = nullptr */

};

