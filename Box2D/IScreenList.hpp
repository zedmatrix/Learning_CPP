#ifndef ISCREENLIST_HPP
#define ISCREENLIST_HPP

#include <memory>
#include <vector>

// Forward Declare
class IGameScreen;
class IMainGame;

class IScreenList {

public:
    IScreenList(std::shared_ptr<IMainGame> game);
    ~IScreenList();

    void destroy();

    std::shared_ptr<IGameScreen> moveNext();
    std::shared_ptr<IGameScreen> movePrevious();

    void setScreen(int nextScreen);
    void addScreen(std::shared_ptr<IGameScreen> newScreen);
    std::shared_ptr<IGameScreen> getCurrent();

protected:

    std::vector<std::shared_ptr<IGameScreen>> m_screens; /* initially empty then nullptr */

    std::shared_ptr<IMainGame> m_game;/* = nullptr*/

    int m_currentScreenIndex = -1;

private:

};

#endif //ISCREENLIST_HPP
