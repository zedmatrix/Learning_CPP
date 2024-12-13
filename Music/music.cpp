#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <cstring>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <map>
#include <unistd.h>
#include "notes.hpp"
// Map keyboard keys to frequencies
bool skipnote = false;
std::map<char, float> keyToFreq = {
    {'a', C}, {'s', D}, {'d', E}, {'f', F}, {'g', G}, {'h', A}, {'j', B},
    {'z', C_Sharp}, {'x', D_Sharp}, {'c', F_Sharp}, {'v', G_Sharp}, {'b', A_Sharp},
};

void generateSineWave(int16_t* buffer, int numSamples, double frequency) {
    for (int i = 0; i < numSamples; ++i) {
        buffer[i] = static_cast<int16_t>(AMPLITUDE * sin(2.0 * M_PI * frequency * i / SAMPLE_RATE));
    }
}

void playFrequency(pa_simple* pa, float frequency, int duration) {
    std::cout << "Playing: " << frequency << " Hz for " << duration << " ms\n";

    int numSamples = SAMPLE_RATE * duration / 1000;
    int16_t* buffer = new int16_t[numSamples];
    if (!buffer) {
        std::cerr << "Failed to allocate audio buffer\n";
        return;
    }
    generateSineWave(buffer, numSamples, frequency);

    int error;
    if (pa_simple_write(pa, buffer, numSamples * sizeof(int16_t), &error) < 0) {
        std::cerr << "PulseAudio write error: " << pa_strerror(error) << "\n";
        delete[] buffer;
        return;
    }

    delete[] buffer;

    if (skipnote) std::this_thread::sleep_for(std::chrono::milliseconds(duration)); skipnote = !skipnote;
}

// Function to interpret and play a song string
void playSong(pa_simple* pa, const std::string& song) {
    int octave = 4;
    int duration = 400;
    for (char key : song) {
        if (key == '+') {
            if (octave < 8) octave++;
        } else if (key == '-') {
            if (octave > 0) octave--;
        } else if (key == 'P') {
            skipnote = !skipnote;
            std::cout << (skipnote ? "Pausing" : "Resuming") << "\n";
        } else {
            auto it = keyToFreq.find(key);
            if (it != keyToFreq.end()) {
                float frequency = it->second * pow(2, octave - 4);
                playFrequency(pa, frequency, duration);
            } else {
                std::cout << "Unknown key: " << key << "\n";
            }
        }
    }
}

int main() {
    // PulseAudio setup 16-bit PCM, little-endian, Sampling rate
    pa_simple* pa = nullptr;
    pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = SAMPLE_RATE,
        .channels = 2
    };

    int error;
    pa = pa_simple_new(nullptr, "SimplePiano", PA_STREAM_PLAYBACK, nullptr, "playback", &ss, nullptr, nullptr, &error);
    if (!pa) {
        std::cerr << "PulseAudio error: " << pa_strerror(error) << "\n";
        return 1;
    }

    // Chopsticks: FE * 6 , DF * 6
    std::string song = "fdPfdPfdPfdPfdPfdPPsfPsfPsfPsfPsfPsfPP";

    playSong(pa, song);
    return 0;
}
