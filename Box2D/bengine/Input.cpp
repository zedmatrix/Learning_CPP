#include "Input.hpp"

void InputManager::update() {
    /// Copies keymap to previous key map
    for (auto& it : m_keyMap) {
        m_prevKeyMap[it.first] = it.second;
    }
}
void InputManager::pressKey(uint32_t keyID) {
    m_keyMap[keyID] = true;
}

void InputManager::releaseKey(uint32_t keyID) {
    m_keyMap[keyID] = false;
}
bool InputManager::isKeyDown(uint32_t keyID) {
    auto it = m_keyMap.find(keyID);
    if (it != m_keyMap.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::isKeyPressed(uint32_t keyID) {
    if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
        return true;
    }
    return false;
}
bool InputManager::wasKeyDown(uint32_t keyID) {
    auto it = m_prevKeyMap.find(keyID);
    if (it != m_prevKeyMap.end()) {
        return it->second;
    }
    return false;
}

void InputManager::setMouseCoords(float x, float y) {
    m_mouseCoords.x = x;
    m_mouseCoords.y = y;
}
