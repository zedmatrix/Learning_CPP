#ifndef NOTES_HPP
#define NOTES_HPP

// Frequencies for one octave (A4 = 440 Hz)
constexpr float C = 261.63;
constexpr float C_Sharp = 277.18;
constexpr float D = 293.66;
constexpr float D_Sharp = 311.13;
constexpr float E = 329.63;
constexpr float F = 349.23;
constexpr float F_Sharp = 369.99;
constexpr float G = 392.00;
constexpr float G_Sharp = 415.30;
constexpr float A = 440.00;
constexpr float A_Sharp = 466.16;
constexpr float B = 493.88;

// Octave multiplier: Multiply a note's frequency by 2^n to change octaves
constexpr float OCTAVE_UP = 2.0;
constexpr float OCTAVE_DOWN = 0.5;

#define SAMPLE_RATE 44100
#define AMPLITUDE 30000
/*
    g++ -o piano piano.cpp -lpulse-simple -lpulse -lm
    g++ -o music music.cpp -lpulse-simple -lpulse -lm
    ./piano
*/
#endif // NOTES_HPP
