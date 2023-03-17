#include "Oscillator.h"
#include "ToneBank.h"
#include <math.h>

#define TWO_PI (3.14159 * 2)

void Oscillator::setFrequency(float lux) {

    //little or no light.
    //C2
    if (lux <= 5.0) {
        frequency_ = C2;
    }

    //A small amount of light.
    //Cs2-B2 //TODO: switch case for notes. we need 12.
    else if (lux > 5.0 && lux <= 100.0) {

    }

    //A moderately-lit room.
    //C3-B3 //TODO: switch case for notes. we need 12.
    else if (lux > 100.0 && lux <= 500.0) {

    }

    //A better-lit room, or outdoors in the shade.
    //C4-B4 //TODO: switch case for notes. we need 12.
    else if (lux > 500.0 && lux <= 1000.0) {

    }

    //A very well-lit room.
    //C5-B5 //TODO: switch case for notes. we need 12.
    else if (lux > 1000.0 && lux <= 5000.0) {

    }

    //Directly below a bright light, or outdoors in near-direct sunlight.
    //C6-B6  //TODO: switch case for notes. we need 12.
    else if (lux > 5000.0 && lux < 10000.0) {

    }

    //direct sunlight.
    //C7
    else if (lux >= 10000.0) {
        frequency_ = C7;
    }

    else {
        frequency_ = A4; //default to A4 if lux reading is invalid or otherwise abnormal.
    }
}

void Oscillator::setSampleRate(int32_t sampleRate) {
    phaseIncrement_ = (TWO_PI * frequency_) / (double) sampleRate;
}

void Oscillator::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Oscillator::render(float *audioData, int32_t numFrames) {

    if (!isWaveOn_.load()) phase_ = 0;

    for (int i = 0; i < numFrames; i++) {

        if (isWaveOn_.load()) {

            // Calculates the next sample value for the sine wave.
            audioData[i] = (float) (sin(phase_) * amplitude_);

            // Increments the phase, handling wrap around.
            phase_ += phaseIncrement_;
            if (phase_ > TWO_PI) phase_ -= TWO_PI;

        } else {
            // Outputs silence by setting sample value to zero.
            audioData[i] = 0;
        }
    }
}
