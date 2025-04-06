#include "Timing.hpp"

FpsLimiter::FpsLimiter() { }

void FpsLimiter::setMaxFPS(float maxFPS) {
    m_maxFPS = maxFPS;
}


void FpsLimiter::begin() {
    m_startTicks = SDL_GetTicks();
}

float FpsLimiter::end() {
    calculateFPS();

    //for fps limiting to _maxFPS
    uint32_t frameTicks = SDL_GetTicks() - m_startTicks;
    if (1000.0f / m_maxFPS > frameTicks) {
        SDL_Delay(1000.0f / m_maxFPS - frameTicks);
    }
    return m_fps;
}

void FpsLimiter::calculateFPS() {
    static const int NUM_SAMPLES = 20;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static uint32_t prevTicks = SDL_GetTicks();
    uint32_t currentTicks;
    currentTicks = SDL_GetTicks();
    m_frameTime = currentTicks - prevTicks;
    prevTicks = currentTicks;

    frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;

    int count;
    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    if (frameTimeAverage > 0) {
        m_fps = 1000.0f / frameTimeAverage;
    } else {
        m_fps = 60.0f;
    }
}
