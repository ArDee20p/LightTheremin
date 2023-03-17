#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef COMP696_LIGHT_SENSOR_TONEBANK_H
#define COMP696_LIGHT_SENSOR_TONEBANK_H

/*
 * Tone bank for output. Rather than using a complex quadratic or other type of equation to map the
 * range from C2 to C7, we simply use predefined note tones from here.
 *
 * The predefined notes were copied from a tone generator site created by Tomasz P. Szynalski.
 * It is available at https://www.szynalski.com/tone-generator/.
 */

//Great octave.
#define C2  65.406
#define Cs2 69.296
#define D2  73.416
#define Ds2 77.782
#define E2  82.407
#define F2  87.307
#define Fs2 92.499
#define G2  97.999
#define Gs2 103.826
#define A2  110.0
#define As2 116.541
#define B2  123.471

//Small octave.
#define C3  130.813
#define Cs3 138.591
#define D3  146.832
#define Ds3 155.563
#define E3  164.814
#define F3  174.614
#define Fs3 184.997
#define G3  195.998
#define Gs3 207.652
#define A3  220.0
#define As3 233.082
#define B3  246.942

//One-line octave.
#define C4  261.626
#define Cs4 277.183
#define D4  293.665
#define Ds4 311.127
#define E4  329.628
#define F4  349.228
#define Fs4 369.994
#define G4  391.995
#define Gs4 415.305
#define A4  440.0
#define As4 466.164
#define B4  493.883

//Two-line octave.
#define C5  523.251
#define Cs5 554.365
#define D5  587.330
#define Ds5 622.254
#define E5  659.255
#define F5  698.456
#define Fs5 739.989
#define G5  783.991
#define Gs5 830.609
#define A5  880.0
#define As5 932.238
#define B5  988.767

//Three-line octave.
#define C6  1046.502
#define Cs6 1108.731
#define D6  1174.659
#define Ds6 1244.508
#define E6  1318.510
#define F6  1396.913
#define Fs6 1479.978
#define G6  1567.982
#define Gs6 1661.219
#define A6  1760.0
#define As6 1864.655
#define B6  1975.533

//Four-line octave. (Only C7 is used.)
#define C7 2093.005

#endif //COMP696_LIGHT_SENSOR_TONEBANK_H

#pragma clang diagnostic pop