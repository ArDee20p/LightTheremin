#ifndef COMP696_LIGHT_SENSOR_OSCILLATOR_H
#define COMP696_LIGHT_SENSOR_OSCILLATOR_H

#include <atomic>
#include <stdint.h>

class Oscillator {
public:
    void setWaveOn(bool isWaveOn);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);
    void setFrequency(float freq);

private:
    std::atomic<bool> isWaveOn_{false};
    double phase_ = 0.0;
    double phaseIncrement_ = 0.0;
    double frequency_ = 1000.0; //default to conventional reference tone.
    double amplitude_ = 0.8;     //TODO: class member currently not variable, but will vary if we can implement a second device to set amplitude.
};

#endif //COMP696_LIGHT_SENSOR_OSCILLATOR_H
