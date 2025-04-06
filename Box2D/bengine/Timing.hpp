#pragma once
#include <SDL2/SDL.h>
#include <cstdint>

class FpsLimiter {

public:
    FpsLimiter();

    void setMaxFPS(float maxFPS);
    void begin();
    float end();

private:

    void calculateFPS();
    float m_maxFPS;
    uint32_t m_startTicks;
    float m_time;

    float m_fps;
    float m_frameTime;
};
