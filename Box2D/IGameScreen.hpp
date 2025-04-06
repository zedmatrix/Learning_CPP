#ifndef IGAMESCREEN_HPP
#define IGAMESCREEN_HPP
#include <memory>

constexpr int SCREEN_INDEX_NO_SCREEN = -1;
enum class ScreenState {
    NONE,
    RUNNING,
    EXIT_APPLICATION,
    CHANGE_NEXT,
    CHANGE_PREVIOUS
};

class IMainGame;
class IGameScreen {

public:
    friend class IScreenList;
    IGameScreen() {
        //Empty
    }
    virtual ~IGameScreen() = default;

    // Called at beginning and end of application
    virtual void build() = 0;
    virtual void destroy() = 0;

    // Called when a screen enters and exits focus
    virtual void onEntry() = 0;
    virtual void onExit() = 0;

    // Called in the maingame loop
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual int getNextScreenIndex() const = 0;
    virtual int getPreviousScreenIndex() const = 0;

    int getScreenIndex() const { return m_screenIndex; }

    ScreenState getState() const { return m_currentState; }
    void setRunning() { m_currentState = ScreenState::RUNNING; }

    void setParentGame(std::shared_ptr<IMainGame> game) { m_game = game; }


protected:
    ScreenState m_currentState = ScreenState::NONE;

    int m_screenIndex = -1;

    //std::weak_ptr<IMainGame> m_game;/* = nullptr*/
    std::shared_ptr<IMainGame> m_game;/* = nullptr*/

private:

};

#endif //IGAMESCREEN_HPP
