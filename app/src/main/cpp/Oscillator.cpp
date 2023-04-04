/*
 * Copyright 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Oscillator.h"
#include "ToneBank.h"
#include <cmath>

double Oscillator::setFrequency(float lux, char mode) {
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
    return frequency_;
}

void Oscillator::setSampleRate(double rate) {
    sampleRate_ = rate;
}

void Oscillator::setPhaseIncrement(int32_t sampleRate) {
    phaseIncrement_ = (TWO_PI * frequency_) / (double) sampleRate_;
}

void Oscillator::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Oscillator::render(float *audioData, int32_t numFrames) {

    setPhaseIncrement(sampleRate_);

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
