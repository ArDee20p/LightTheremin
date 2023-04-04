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

#include <android/log.h>
#include <oboe/Oboe.h>
#include "AudioEngine.h"
#include <thread>
#include <mutex>

// Double-buffering offers a good tradeoff between latency and protection against glitches.
constexpr int32_t kBufferSizeInBursts = 2;

int32_t AudioEngine::start() {
    std::lock_guard<std::mutex> lock(mLock);
    oboe::AudioStreamBuilder streamBuilder;
    oboe::Result result = streamBuilder.setPerformanceMode(oboe::PerformanceMode::LowLatency)
    ->setSharingMode(oboe::SharingMode::Exclusive)
    ->setFormat(oboe::AudioFormat::Float)
    ->setSampleRate(48000)
    ->setChannelCount(1)
    ->setDeviceId(2) //TODO: is there a way to grab deviceID of Bluetooth speaker at runtime?
    ->setDataCallback(oscillator_.onAudioReady())
    ->openStream(mStream);
    if (result != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR, "AudioEngine", "Error opening stream %s",
                            oboe::convertToText(result));
        return (int32_t) result;
    }

    // Retrieves the sample rate of the stream for our oscillator.
    oscillator_.setSampleRate(48000);

    // Sets the buffer size.
    mStream->setBufferSizeInFrames(mStream->getFramesPerBurst() * kBufferSizeInBursts);

    // Starts the stream.
    result = mStream->requestStart();
    if (result != oboe::Result::OK) {
        __android_log_print(ANDROID_LOG_ERROR, "AudioEngine", "Error starting stream %s",
                            oboe::convertToText(result));
        return (int32_t) result;
    }
    return (int32_t) result;
}

void AudioEngine::stop() {
    std::lock_guard<std::mutex> lock(mLock);
    if (mStream) {
        mStream->requestStop();
        mStream->close();
        mStream.reset();
    }
}

void AudioEngine::setToneOn(bool isToneOn) {
    oscillator_.setWaveOn(isToneOn);
}
