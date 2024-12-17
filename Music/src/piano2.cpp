#include <iostream>
#include <cmath>
#include <cstring>
#include <pulse/simple.h>
#include <pulse/error.h>
#include <map>
#include <termios.h>
#include <unistd.h>
#include "notes.hpp"
#include "print.hpp"

int16_t* buffer;

int16_t* generateSineWave(int numSamples, double frequency) {
    buffer = new int16_t[numSamples];
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

// Function to capture a single key press
char getKey() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::cin >> ch;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    const float duration = 0.5;
    int numSamples;

    // Map keyboard keys to frequencies
    std::map<char, float> keyToFreq = {
        {'a', C}, {'s', D}, {'d', E}, {'f', F}, {'g', G}, {'h', A}, {'j', B},
        {'z', C_Sharp}, {'x', D_Sharp}, {'c', F_Sharp}, {'v', G_Sharp}, {'b', A_Sharp},
        {'w', C_Flat}, {'e', D_Flat}, {'r', E_Flat}, {'t', F_Flat}, {'y', G_Flat}, {'u', A_Flat}, {'i', B_Flat},
    };

    pa_simple* pa = InitPulseAudio();
    if (!pa) {
        std::cerr << "Failed to initialize PulseAudio.\n";
        return 1;
    }

    print("Press keys (a, s, d, f, g, h, j and z, x, c, v, b) to play tones.\n(+, - to change octaves)\nPress ESC to quit.\n");

    char keystroke;
    int octave = 4;
    while (keystroke != 27) {
        if (keystroke == '-') {
            if (octave > 0) octave--; continue;
        }
        if (keystroke == '+') {
            if (octave < 8) octave++; continue;
        }

        auto it = keyToFreq.find(keystroke);
        if (it != keyToFreq.end()) {
            double frequency = it->second * pow(2, octave - 4);

            // Generate a short tone
            numSamples = SAMPLE_RATE * duration;
            buffer = generateSineWave(numSamples, frequency);

            if (buffer) {
                if (PlayNote(pa, buffer, numSamples)) {
                    delete[] buffer;
                    buffer = nullptr;
                }
            } else {
                std::cerr << "Failed to allocate buffer.\n";
            }
        } else {
            print("Key not mapped to any tone.\n");
        }
        keystroke = getKey();
    }

    // Cleanup
    if (buffer) {
        delete[] buffer;
        buffer = nullptr;
    }
    if (pa) {
        pa_simple_free(pa);
    }
    return 0;
}
