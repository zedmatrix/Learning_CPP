#include <iostream>
#include <cmath>
#include <cstring>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <map>
#include <unistd.h>
#include "notes.hpp"
#include "print.hpp"

int16_t* generateSineWave(int numSamples, double frequency) {
    int16_t* buffer = new int16_t[numSamples];
    if (!buffer) {
        return nullptr;
    }
    for (int i = 0; i < numSamples; ++i) {
        buffer[i] = static_cast<int16_t>(AMPLITUDE * sin(2.0 * M_PI * frequency * i / SAMPLE_RATE));
    }
    return buffer;
}

pa_simple* InitPulseAudio() {
    // PulseAudio setup 16-bit PCM, little-endian, Sampling rate
    pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = SAMPLE_RATE,
        .channels = 2
    };
    int error;
    pa_simple* pa = pa_simple_new(
        nullptr,
        "SimplePiano",
        PA_STREAM_PLAYBACK,
        nullptr,
        "playback",
        &ss,
        nullptr,
        nullptr,
        &error
    );
    if (!pa) {
        std::cerr << "PulseAudio error: " << pa_strerror(error) << "\n";
        return nullptr;
    }
    return pa;
}

bool PlayNote(pa_simple* pa, const int16_t* buffer, size_t numSamples) {
    int error;
    if (pa_simple_write(pa, buffer, numSamples * sizeof(int16_t), &error) < 0) {
        std::cerr << "PulseAudio write error: " << pa_strerror(error) << "\n";
        return false;
    }
    return true;
}

int main() {
    const float duration = 0.75;
    int numSamples;
    int16_t* buffer;

    // Map keyboard keys to frequencies
    std::map<char, float> keyToFreq = {
        {'a', C}, {'s', D}, {'d', E}, {'f', F}, {'g', G}, {'h', A}, {'j', B},
        {'z', C_Sharp}, {'x', D_Sharp}, {'c', F_Sharp}, {'v', G_Sharp}, {'b', A_Sharp},
    };

    pa_simple* pa = InitPulseAudio();
    if (!pa) {
        std::cerr << "Failed to initialize PulseAudio.\n";
        return 1;
    }

    print("Press keys (a, s, d, f, g, h, j and z, x, c, v, b) to play tones.\n(+, - to change octaves) Press Q to quit.\n");

    char key;
    int octave = 4;
    while (std::cin >> key) {
        if (key == 'Q' || key == 'q') break;
        if (key == '-') {
            if (octave > 0) octave--; continue;
        }
        if (key == '+') {
            if (octave < 8) octave++; continue;
        }
        auto it = keyToFreq.find(key);
        if (it != keyToFreq.end()) {
            double frequency = it->second * pow(2, octave - 4);

            // Generate a short tone
            numSamples = SAMPLE_RATE * duration;
            int16_t* buffer = generateSineWave(numSamples, frequency);

            if (buffer) {
                if (!PlayNote(pa, buffer, numSamples)) {
                    std::cerr << "Failed to play note.\n";
                }

            } else {

                std::cerr << "Failed to allocate buffer.\n";
            }

        } else {
            print("Key not mapped to any tone.\n");
        }
    }

    // Cleanup
    if (pa) {
        delete[] buffer;
        pa_simple_free(pa);
    }
    return 0;
}
