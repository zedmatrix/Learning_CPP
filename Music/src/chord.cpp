#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <cstring>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <map>
#include <unistd.h>
#include <vector>
#include "notes.hpp"

// Global Values
bool skipnote = false;
int octave = 4;
int bpm = 120;
int tempo = 4;
int duration = 60000 / bpm * tempo;

// Map keyboard keys to frequencies
std::map<char, float> keyToFreq = {
    {'C', C}, {'D', D}, {'E', E}, {'F', F}, {'G', G}, {'A', A}, {'B', B},
    {'c', C_Sharp}, {'d', D_Sharp}, {'e', E_Sharp}, {'f', F_Sharp}, {'g', G_Sharp}, {'a', A_Sharp},
};

void generateSineWave(int16_t* buffer, int numSamples, const std::vector<float>& frequencies) {
    for (int i = 0; i < numSamples; ++i) {
        float sample = 0.0f;
        for (float frequency : frequencies) {
            sample += sin(2.0 * M_PI * frequency * i / SAMPLE_RATE); // Sum the sine waves
        }
        buffer[i] = static_cast<int16_t>(AMPLITUDE * sample);
    }
}

void playChord(pa_simple* pa, const std::vector<float>& frequencies) {
    print("Playing chord with frequencies: ");
    for (float freq : frequencies) {
        std::cout << freq << " ";
    }
    std::cout << "\n";

    int numSamples = SAMPLE_RATE * duration / 1000;
    int16_t* buffer = new int16_t[numSamples];

    if (!buffer) {
        std::cerr << "Failed to allocate audio buffer\n";
        return;
    }

    generateSineWave(buffer, numSamples, frequencies);

    int error;
    if (pa_simple_write(pa, buffer, numSamples * sizeof(int16_t), &error) < 0) {
        std::cerr << "PulseAudio write error: " << pa_strerror(error) << "\n";
        delete[] buffer;
        return;
    }

    delete[] buffer;
}
// Function to interpret and play a song string
void playSong(pa_simple* pa, const std::string& song) {
    std::vector<float> chord;
    for (char key : song) {
        if (key == ' ') {
            chord.clear();
            //std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        } else if (key == '+') {
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
                chord.push_back(frequency);
                playChord(pa, chord);
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
    std::string song = "-1F +d -E +d -F +d -E +d -F +c -E +c -F +c -E +c";
    playSong(pa, song);
    // for (int i=0; i<3; i++) {
    //     playSong(pa, song);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    // }

    return 0;
}
