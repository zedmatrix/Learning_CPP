#ifndef NOTES_HPP
#define NOTES_HPP

// Frequencies for one octave (A4 = 440 Hz)
constexpr float C = 261.63;
constexpr float C_Sharp = 277.18;
constexpr float D = 293.66;
constexpr float D_Sharp = 311.13;
constexpr float E = 329.63;
constexpr float E_Sharp = 346.23;
constexpr float F = 349.23;
constexpr float F_Sharp = 369.99;
constexpr float G = 392.00;
constexpr float G_Sharp = 415.30;
constexpr float A = 440.00;
constexpr float A_Sharp = 466.16;
constexpr float B = 493.88;
// Flats
constexpr float A_Flat = 415.30;
constexpr float B_Flat = 466.16;
constexpr float C_Flat = 554.37;
constexpr float D_Flat = 523.25;
constexpr float E_Flat = 622.25;
constexpr float F_Flat = 698.46;
constexpr float G_Flat = 740.00;
// Flats
// constexpr float A_Flat = 783.99;
// constexpr float B_Flat = 932.33;
// constexpr float C_Flat = 932.33;
// constexpr float D_Flat = 1046.50;
// constexpr float E_Flat = 1174.66;
// constexpr float F_Flat = 1318.51;
// constexpr float G_Flat = 1396.91;

// Octave multiplier: Multiply a note's frequency by 2^n to change octaves
constexpr float OCTAVE_UP = 2.0;
constexpr float OCTAVE_DOWN = 0.5;

#define SAMPLE_RATE 48000
#define AMPLITUDE 30000

#endif // NOTES_HPP
