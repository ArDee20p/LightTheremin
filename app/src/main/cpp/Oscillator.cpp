#include "Oscillator.h"
#include "ToneBank.h"
#include <cmath>

#define TWO_PI (3.14159 * 2)
#define CONST1 58.6491111111109

void Oscillator::setFrequency(float lux, char mode) {
    if (mode == 'I') {     //Indoor Mode
        if (lux <= 5000) {
            frequency_ = (2.48202962962963E-08 * pow(lux, 3)) -
                         (7.05423650793653E-05 * pow(lux, 2)) +
                         (0.137616116402117 * lux) + CONST1;
        }
        else {
            frequency_ = C7;
        }
    }
    else if (mode == 'O') { //Outdoor Mode
        if (lux <= 10000) {
            frequency_ = (3.10253703703704E-09 * pow(lux, 3)) -
                         (1.76355912698413E-05 * pow(lux, 2)) +
                         (0.0688080582010584 * lux) + CONST1;
        }
        else {
            frequency_ = C7;
        }
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
