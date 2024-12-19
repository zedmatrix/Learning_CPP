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
int duration = 60000 / (bpm * tempo);

// Map keys to frequencies (from notes.hpp)
std::map<char, float> keyToFreq = {
    {'c', C}, {'d', D}, {'e', E}, {'f', F}, {'g', G}, {'a', A}, {'b', B},
    {'C', C_Flat}, {'D', D_Flat}, {'E', E_Flat}, {'F', F_Flat}, {'G', G_Flat}, {'A', A_Flat}, {'B', B_Flat},
};

void generateSineWave(int16_t* buffer, int numSamples, double frequency) {
    for (int i = 0; i < numSamples; ++i) {
        buffer[i] = static_cast<int16_t>(AMPLITUDE * sin(2.0 * M_PI * frequency * i / SAMPLE_RATE));
    }
}

void playFrequency(pa_simple* pa, float frequency) {
    duration = 60000 / (bpm * tempo);
    int numSamples = SAMPLE_RATE * duration / 1000;
    int16_t* buffer = new int16_t[numSamples];

    //std::cout << "Playing: " << frequency << " Hz for " << duration << " ms\n";
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
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
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

    // flats=CDEFGA  normal=cdefgab
    // std::string flat_scales = "t1o1CDEFGAB t1o2CDEFGAB t1o3CDEFGAB t1o4CDEFGAB t2o5CDEFGAB t2o6CDEFGAB t2o7CDEFGAB";
    // playSong(pa, flat_scales);
    // std::string scales = "t1o1cdefgab t1o2cdefgab t1o3cdefgab t1o4cdefgab t2o5cdefgab t2o6cdefgab t2o7cdefgab";
    // playSong(pa, scales);

    print("Playing Twinkle Twinkle in C\n");
    std::string twinkle_little_star = "t2o4ccggaagt2o4ffeeddct2o4ggffeedt2o4ggffeedt2o4ccggaagt2o4ffeeddct1 ";
    playSong(pa, twinkle_little_star);

    print("Playing Jingle Bells in C Major - Moderately Fast Tempo\n");
    std::string jingle_bells = "t2o4eeeeeeegcdet2o4fffffeeeddedgt2o4eeeeeeegcdet2o4fffffeeggfDct1 ";
    playSong(pa, jingle_bells);

    print("Playing Happy Brithday in C Major\n");
    std::string happy_birthday = "t2o4ccddccffEEt2o4ccddccggFFt2o4cccaFEDt2o4bbAFgFt1 ";
    playSong(pa, happy_birthday);

    return 0;
}
