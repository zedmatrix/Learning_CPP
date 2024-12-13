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
int octave = 4;
int bpm = 120;
int tempo = 1;
int duration = 60000 / bpm * tempo;

std::map<char, float> keyToFreq = {
    {'C', C}, {'D', D}, {'E', E}, {'F', F}, {'G', G}, {'A', A}, {'B', B},
    {'c', C_Sharp}, {'d', D_Sharp}, {'e', E_Sharp}, {'f', F_Sharp}, {'g', G_Sharp}, {'a', A_Sharp},
};

void generateSineWave(int16_t* buffer, int numSamples, double frequency) {
    for (int i = 0; i < numSamples; ++i) {
        buffer[i] = static_cast<int16_t>(AMPLITUDE * sin(2.0 * M_PI * frequency * i / SAMPLE_RATE));
    }
}

void playFrequency(pa_simple* pa, float frequency) {
    std::cout << "Playing: " << frequency << " Hz for " << duration << " ms\n";

    if (skipnote) { duration = 200; }
    int numSamples = SAMPLE_RATE * duration / 1000;
    int16_t* buffer = new int16_t[numSamples];
    if (!buffer) {
        std::cerr << "Failed to allocate audio buffer\n";
        return;
    }
    for (int i = 0; i < 2; ++i) {
        generateSineWave(buffer, numSamples, frequency);
    }


    //generateSineWave(buffer, numSamples, frequency);

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
    for (char key : song) {
        if (key == '+') {
            if (octave < 8) octave++;
        } else if (key == '-') {
            if (octave > 0) octave--;
        } else if (key == 'P') {
            skipnote = !skipnote;
            std::cout << (skipnote ? "Pausing" : "Resuming") << "\n";
        } else if (key == '1') {
            duration = 60000 / bpm * 1;
        } else if (key == '2') {
            duration = 60000 / bpm * 2;
        } else if (key == '3') {
            duration = 60000 / bpm * 3;
        } else if (key == '4') {
            duration = 60000 / bpm * 4;
        } else {
            auto it = keyToFreq.find(key);
            if (it != keyToFreq.end()) {
                float frequency = it->second * pow(2, octave - 4);
                playFrequency(pa, frequency);
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

    // Chopsticks: FE * 6 , DF * 6 "fdfdPfdfdPffddPffddPffddPffddPPsfPsfPsfPsfPsfPsfPP"
    std::string song = "-1FE1FE+1DF1DF-";
    for (int i=0; i<3; i++) {
        playSong(pa, song);
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }

    return 0;
}
