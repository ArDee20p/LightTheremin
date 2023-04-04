
#include <oboe/Oboe.h>
#include <oboe/LatencyTuner.h>
#include "OscillatorCallback.h"

oboe::DataCallbackResult
OscillatorCallback::onAudioReady(oboe::AudioStream *audioStream, void *audioData,
                                 int32_t numFrames) {
    if (audioStream != mStream) {
        mStream = audioStream;
        mLatencyTuner = std::make_unique<oboe::LatencyTuner>(*audioStream);
    }
    if (mBufferTuneEnabled && mLatencyTuner && audioStream->getAudioApi() == oboe::AudioApi::AAudio) {
        mLatencyTuner->tune();
    }
    auto underrunCountResult = audioStream->getXRunCount();
    int bufferSize = audioStream->getBufferSizeInFrames();

    auto result =

    return oboe::DataCallbackResult::Stop;
}

void OscillatorCallback::useStream(std::shared_ptr<oboe::AudioStream> stream) {

}
