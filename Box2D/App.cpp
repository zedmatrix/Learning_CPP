#include "App.hpp"
#include "IGameScreen.hpp"
#include "IScreenList.hpp"
#include <stdexcept>
#include <iostream>
#include "ResourceManager.hpp"
#include <ctime>

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
    b2Vec2 gravity(0.0f, -9.81f);
    m_world = std::make_unique<b2World>(gravity);

    //Make Ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -15.0f);
    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    // Make the ground fixture
    b2PolygonShape groundBox;
    groundBox.SetAsBox(20.0f, 0.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Make a bunch of boxes
    std::mt19937 randGenerator(time(NULL));
    std::uniform_real_distribution<float> xPos(-9.0, 9.0f);
    std::uniform_real_distribution<float> yPos(0.0f, 10.0f);

    std::uniform_real_distribution<float> size(0.5, 2.5f);
    std::uniform_int_distribution<int> color(50, 255);
    std::uniform_real_distribution<float> angleDist(-1.0f, 1.0f);


    const int NUM_BOXES = 50;

    for (int i = 0; i < NUM_BOXES; i++) {
        ColorRGBA8 randColor;
        randColor.r = color(randGenerator);
        randColor.g = color(randGenerator);
        randColor.b = color(randGenerator);
        randColor.a = 255;
        float s = size(randGenerator);
        float angle = angleDist(randGenerator);
        Box newBox;
        newBox.init(m_world.get(),
                    glm::vec2(xPos(randGenerator), yPos(randGenerator)),
                    glm::vec2(s, s), randColor, angle);
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

}
void GameScreens::onExit() {
    std::cout << "Exit\n";
}

// Called in the maingame loop
void GameScreens::update() {
    m_camera.update();
    checkInput();
    // Update Physics for Box
    m_world->Step(1.0f / 60.0f, 6, 2);
}
void GameScreens::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.3f, 0.4f, 0.3f, 0.5f);
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

    m_texture = ResourceManager::getTexture("assets/bricks.png");
    for (auto& b : m_boxes) {
        glm::vec4 destRect;
        destRect.x = b.getPosition().x - b.getDimensions().x / 2.0f;
        destRect.y = b.getPosition().y - b.getDimensions().y / 2.0f;
        destRect.z = b.getDimensions().x;
        destRect.w = b.getDimensions().y;

        m_spriteBatch.draw(destRect, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                           m_texture.id, 0.0f, b.getColor(), b.getBody()->GetAngle());
    }
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    m_textureProgram.unuse();
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
