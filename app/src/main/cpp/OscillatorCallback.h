#ifndef COMP696_LIGHT_SENSOR_OSCILLATORCALLBACK_H
#define COMP696_LIGHT_SENSOR_OSCILLATORCALLBACK_H

#include <oboe/Oboe.h>
#include <oboe/LatencyTuner.h>
#include "Oscillator.h"

class OscillatorCallback : public oboe::AudioStreamDataCallback {
public:
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;

    void setBufferTuneEanbled(bool enabled) {mBufferTuneEnabled = enabled;}

    void useStream(std::shared_ptr<oboe::AudioStream> stream);

private:
    bool mBufferTuneEnabled = true;
    std::unique_ptr<oboe::LatencyTuner> mLatencyTuner;
    oboe::AudioStream *mStream = nullptr;
};


#endif //COMP696_LIGHT_SENSOR_OSCILLATORCALLBACK_H
