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
#include "print.hpp"

// Globals
int octave = 4;
int bpm = 120;
int tempo = 1;
int duration = 60000 / bpm * tempo;

// Map keys to frequencies (from notes.hpp)
std::map<char, float> keyToFreq = {
    {'c', C}, {'d', D}, {'e', E}, {'f', F}, {'g', G}, {'a', A}, {'b', B},
    {'C', C_Sharp}, {'D', D_Sharp}, {'E', E_Sharp}, {'F', F_Sharp}, {'G', G_Sharp}, {'A', A_Sharp},
};

void generateSineWave(int16_t* buffer, int numSamples, double frequency) {
    for (int i = 0; i < numSamples; ++i) {
        buffer[i] = static_cast<int16_t>(AMPLITUDE * sin(2.0 * M_PI * frequency * i / SAMPLE_RATE));
    }
}

void playFrequency(pa_simple* pa, float frequency) {
    duration = 60000 / bpm * tempo;
    int numSamples = SAMPLE_RATE * duration / 1000;
    int16_t* buffer = new int16_t[numSamples];

    std::cout << "Playing: " << frequency << " Hz for " << duration << " ms\n";
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
}

// Function to interpret and play a song string
void playSong(pa_simple* pa, const std::string& song) {
    bool SetOctave {false};
    bool SetTempo {false};
    for (char key : song) {
        if (key == ' ') {
            std::this_thread::sleep_for(std::chrono::milliseconds(duration));
            continue;
        }
        if (key == 'o') {
            SetOctave = true;
            continue;
        }
        if (SetOctave) {
            if (key >= '1' && key <= '7') {
                octave = key - '0';
                print("Octave: {}\n", key);
                SetOctave = false;
                continue;
            } else {
                std::cerr << "Invalid Octave." << key <<"\n";
                SetOctave = false;
                continue;
            }
        }

        if (key == 't') {
            SetTempo = true;
            continue;
        }
        if (SetTempo) {
            if (key >= '1' && key <= '4') {
                tempo = key - '0';
                print("Tempo: {}\n", key);
                SetTempo = false;
                continue;
            } else {
                std::cerr << "Invalid Tempo." << key <<"\n";
                SetTempo = false;
                continue;
            }
        }
        auto it = keyToFreq.find(key);
        if (it != keyToFreq.end()) {
            float frequency = it->second * pow(2, octave - 4);
            playFrequency(pa, frequency);
        } else {
            std::cerr << "Unknown key: " << key << "\n";
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

    // sharps=CDEFGA  normal=cdefgab
    std::string song = "t2o1cdefgab o2cdefgab o3cdefgab o4cdefgab o5cdefgab o6cdefgab t1o7cdefgab";
    playSong(pa, song);

    // for (int i=0; i<3; i++) {
    //     playSong(pa, song);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    // }

    return 0;
}
