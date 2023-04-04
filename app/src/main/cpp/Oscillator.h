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

#ifndef COMP696_LIGHT_SENSOR_OSCILLATOR_H
#define COMP696_LIGHT_SENSOR_OSCILLATOR_H

#include <atomic>
#include <stdint.h>

#define TWO_PI (3.14159 * 2)
#define CONST1 58.6491111111109

class Oscillator {
public:
    void setWaveOn(bool isWaveOn);
    void setSampleRate(double rate);
    void setPhaseIncrement(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);
    double setFrequency(float freq, char mode);

private:
    std::atomic<bool> isWaveOn_{false};
    double phase_ = 0.0;
    double phaseIncrement_ = 0.0;
    double frequency_ = 1000.0; //default to conventional reference tone.
    double amplitude_ = 1;
    double sampleRate_ = 48000.0;
};

#endif //COMP696_LIGHT_SENSOR_OSCILLATOR_H
