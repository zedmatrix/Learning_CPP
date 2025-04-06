#ifndef IMAINGAME_HPP
#define IMAINGAME_HPP

#include "IMainWindow.hpp"
#include "IScreenList.hpp"
#include "Input.hpp"
#include <memory>

class IScreenList;
class IGameScreen;

class IMainGame : public std::enable_shared_from_this<IMainGame> {

public:
    IMainGame();
    virtual ~IMainGame() = default;

    void run();
    void exitGame();
    void onSDLEvent(SDL_Event& evnt);
    virtual void onInit() = 0;
    virtual void addScreens() = 0;
    virtual void onExit() = 0;

    const float getFps() { return m_fps; }

protected:
    virtual void update();
    virtual void draw();


    bool init();
    bool initSystems();

    std::shared_ptr<IScreenList> m_screenList;    /* = nullptr*/
    std::shared_ptr<IGameScreen> m_currentScreen; /* = nullptr*/
    bool m_isRunning = false;
    float m_fps = 0.0f;
    IMainWindow m_window;
    InputManager m_inputManager;

private:
    std::string m_title = "Demo";
    int m_screenWidth = 1024;
    int m_screenHeight = 768;

};

#endif //IMAINGAME_HPP
