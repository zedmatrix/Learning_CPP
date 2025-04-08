#include "IMainGame.hpp"
#include "Timing.hpp"
#include "IGameScreen.hpp"
#include <iostream>

IMainGame::IMainGame() {

}

void IMainGame::run() {
    m_screenList = std::make_shared<IScreenList>(shared_from_this());

    if (!init()) return;
    FpsLimiter limiter;
    limiter.setMaxFPS(60.0f);

    m_isRunning = true;

    while (m_isRunning) {
        limiter.begin();

        inputManager.update();

        update();

        draw();

        m_fps = limiter.end();
        m_window.swapBuffer();
    }

}
void IMainGame::exitGame() {
    m_currentScreen->onExit();
    if (m_screenList) {
        m_screenList->destroy();
        m_screenList.reset();
    }
    m_isRunning = false;
}
void IMainGame::onSDLEvent(SDL_Event& evnt) {
    switch (evnt.type) {
        case SDL_QUIT:
            exitGame();
            break;
        case SDL_MOUSEMOTION:
            inputManager.setMouseCoords((float)evnt.motion.x, (float)evnt.motion.y);
            break;
        case SDL_KEYDOWN:
            inputManager.pressKey(evnt.key.keysym.sym);
            break;
        case SDL_KEYUP:
            inputManager.releaseKey(evnt.key.keysym.sym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            inputManager.pressKey(evnt.button.button);
            break;
        case SDL_MOUSEBUTTONUP:
            inputManager.releaseKey(evnt.button.button);
            break;
    }
}

bool IMainGame::init() {
    // Bengine::init()
    // Initialize Everything and Set Up Double Buffering
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        IMainWindow::fatalError("SDL_Init Error: " + std::string(SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    // end of Bengine::init()

    m_title = "IMainGame Demo";
    m_screenWidth = 1024;
    m_screenHeight = 768;
    if (!initSystems()) return false;

    onInit();
    addScreens();
    m_currentScreen = m_screenList->getCurrent();
    m_currentScreen->onEntry();
    m_currentScreen->setRunning();
    return true;
}

bool IMainGame::initSystems() {
    m_window.create(m_title, m_screenWidth, m_screenHeight, 0);
    return true;
}

void IMainGame::update() {
    if (m_currentScreen) {
        switch (m_currentScreen->getState()) {
            case ScreenState::RUNNING:
                m_currentScreen->update();
                break;
            case ScreenState::CHANGE_NEXT:
                m_currentScreen->onExit();
                m_currentScreen = m_screenList->moveNext();
                if (m_currentScreen) {
                    m_currentScreen->setRunning();
                    m_currentScreen->onEntry();
                }
                break;
            case ScreenState::CHANGE_PREVIOUS:
                m_currentScreen->onExit();
                m_currentScreen = m_screenList->movePrevious();
                if (m_currentScreen) {
                    m_currentScreen->setRunning();
                    m_currentScreen->onEntry();
                }
                break;
            case ScreenState::EXIT_APPLICATION:
                exitGame();
                break;
            default:
                break;

        }
    } else {
        exitGame();
    }
}

void IMainGame::draw() {
    glViewport(0, 0, m_window.getScreenWidth(), m_window.getScreenHeight());

    if (m_currentScreen) {
        if (m_currentScreen->getState() == ScreenState::RUNNING) {
            m_currentScreen->draw();
        }
    }
}
