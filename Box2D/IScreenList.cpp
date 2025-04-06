#include "IScreenList.hpp"
#include "IGameScreen.hpp"

IScreenList::IScreenList(std::shared_ptr<IMainGame> game) : m_game(std::move(game)) {
    // Empty
}

IScreenList::~IScreenList() {
    destroy();
}
void IScreenList::destroy() {
    for (auto& screen : m_screens) {
        screen->destroy();
    }
    m_screens.resize(0);
    m_currentScreenIndex = SCREEN_INDEX_NO_SCREEN;
}

std::shared_ptr<IGameScreen> IScreenList::moveNext() {
    std::shared_ptr<IGameScreen> currentScreen = getCurrent();
    if (currentScreen->getNextScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
        m_currentScreenIndex = currentScreen->getNextScreenIndex();
    }
    return getCurrent();
}

std::shared_ptr<IGameScreen> IScreenList::movePrevious() {
    std::shared_ptr<IGameScreen> currentScreen = getCurrent();
    if (currentScreen->getPreviousScreenIndex() != SCREEN_INDEX_NO_SCREEN) {
        m_currentScreenIndex = currentScreen->getPreviousScreenIndex();
    }
    return getCurrent();
}

void IScreenList::setScreen(int nextScreen) {
    m_currentScreenIndex = nextScreen;

}

void IScreenList::addScreen(std::shared_ptr<IGameScreen> newScreen) {
    // size_t index = m_screens.size();
    // newScreen->m_screenIndex = index;
    newScreen->m_screenIndex = m_screens.size();
    newScreen->build();
    newScreen->setParentGame(m_game);
    m_screens.emplace_back(std::move(newScreen));
}

std::shared_ptr<IGameScreen> IScreenList::getCurrent() {
    if (m_currentScreenIndex == SCREEN_INDEX_NO_SCREEN) return nullptr;
    return m_screens[m_currentScreenIndex];
}
