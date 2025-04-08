#include "App.hpp"
#include "ResourceManager.hpp"
#include "IGameScreen.hpp"
#include "IScreenList.hpp"
#include <stdexcept>
#include <iostream>
#include <ctime>

const float SCALE_SPEED = 0.05f;

GameScreens::GameScreens(IMainWindow* window) : m_window(window) {
    //Empty
}
int GameScreens::getNextScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}
int GameScreens::getPreviousScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}
void GameScreens::build() {
    std::cout << "build\n";
}
void GameScreens::destroy() {
    std::cout << "destroy\n";
}

// Called when a screen enters and exits focus
void GameScreens::onEntry() {
    b2Vec2 gravity(0.0f, -15.0f);
    m_world = std::make_unique<b2World>(gravity);

    m_debugRenderer.init();
    //Make Ground
    GLTexture groundTexture = ResourceManager::getTexture("assets/steel.png");
    Box groundBox;
    groundBox.init(m_world.get(), glm::vec2(0.0f, -20.0f), glm::vec2(100.0f, 5.0f),
                   groundTexture, ColorRGBA8(255, 255, 255, 255), false, false);
    m_boxes.push_back(groundBox);

    // Make a bunch of boxes
    std::mt19937 randGenerator(time(NULL));
    std::uniform_real_distribution<float> xPos(-10.0f, 25.0f);
    std::uniform_real_distribution<float> yPos(-10.0f, 25.0f);

    std::uniform_real_distribution<float> size(1.5, 3.5f);
    std::uniform_int_distribution<int> color(50, 255);
    std::uniform_real_distribution<float> angleDist(-2.0f, 2.0f);

    m_texture = ResourceManager::getTexture("assets/bricks.png");
    const int NUM_BOXES = 20;

    for (int i = 0; i < NUM_BOXES; i++) {
        ColorRGBA8 randColor;
        randColor.r = color(randGenerator);
        randColor.g = color(randGenerator);
        randColor.b = color(randGenerator);
        randColor.a = 255;
        float s = size(randGenerator);
        Box newBox;
        newBox.init(m_world.get(), glm::vec2(xPos(randGenerator), yPos(randGenerator)),
                    glm::vec2(s, s), m_texture, randColor, true, false, angleDist(randGenerator));
        m_boxes.push_back(newBox);
    }

    m_spriteBatch.init();
    // Compile our texture shader
    m_textureProgram.compileShaders("assets/VertexShader", "assets/FragmentShader");
    m_textureProgram.addAttribute("vertexPosition");
    m_textureProgram.addAttribute("vertexColor");
    m_textureProgram.addAttribute("vertexUV");
    m_textureProgram.linkShaders();
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
    m_camera.setScale(16.0f);

    // Init Player

    m_player.init(m_world.get(), glm::vec2(0.0f, 20.0f),
                  glm::vec2(2.1f, 3.1f), glm::vec2(2.0f, 3.0f),   //drawDims, collisonDims
                  ColorRGBA8(255, 255, 255, 255));

}
void GameScreens::onExit() {
    std::cout << "Exit\n";
}

// Called in the maingame loop
void GameScreens::update() {
    m_camera.update();

    checkInput();

    m_player.update(m_game->inputManager);

    if (m_game->inputManager.isKeyPressed(SDLK_z)) m_camera.setScale(m_camera.getScale() + SCALE_SPEED);
    if (m_game->inputManager.isKeyPressed(SDLK_x)) m_camera.setScale(m_camera.getScale() - SCALE_SPEED);
    // Update Physics for Box
    m_world->Step(1.0f / 60.0f, 6, 2);
}
void GameScreens::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 0.5f);
    m_textureProgram.use();

    // Upload texture uniform
    GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);
    glActiveTexture(GL_TEXTURE0);

    // Camera matrix
    glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
    GLint pUniform = m_textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
    m_spriteBatch.begin();

    for (auto& b : m_boxes) {
        b.draw(m_spriteBatch);
    }
    m_player.draw(m_spriteBatch);
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    m_textureProgram.unuse();
    // Debug Renderer
    if (m_renderDebug) {
        glm::vec4 destRect;
        for (auto& b : m_boxes) {
            destRect.x = b.getBody()->GetPosition().x - b.getDimensions().x / 2.0f;
            destRect.y = b.getBody()->GetPosition().y - b.getDimensions().y / 2.0f;
            destRect.z = b.getDimensions().x;
            destRect.w = b.getDimensions().y;
            m_debugRenderer.drawBox(destRect, ColorRGBA8(200, 200, 200, 200), b.getBody()->GetAngle());
            /*m_debugRenderer.drawCircle(glm::vec2(b.getBody()->GetPosition().x, b.getBody()->GetPosition().y),
                                       ColorRGBA8(200, 200, 200, 200),
                                       b.getDimensions().y / 2.0f);*/
        }
        // Render Player
        m_player.drawDebug(m_debugRenderer);
        m_debugRenderer.end();
        m_debugRenderer.render(projectionMatrix, 2.0f);
    }
}
void GameScreens::checkInput() {
    SDL_Event evnt;
    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        m_game->onSDLEvent(evnt);
    }
}

/// App Functions called from main.cpp
App::App() {
    //Empty
}
void App::onInit() {
    std::cout << "On Init\n";
}

void App::addScreens() {

    m_gameScreens = std::make_shared<GameScreens>(&m_window);
    m_screenList->addScreen(m_gameScreens);
    m_screenList->setScreen(m_gameScreens->getScreenIndex());
}

void App::onExit()  {
    std::cout << "On Exit\n";
}
