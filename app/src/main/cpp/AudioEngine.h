#ifndef COMP696_LIGHT_SENSOR_AUDIOENGINE_H
#define COMP696_LIGHT_SENSOR_AUDIOENGINE_H

#include "../../../../../../AppData/Local/Android/Sdk/ndk/23.1.7779620/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/aaudio/AAudio.h"
#include "Oscillator.h"

class AudioEngine {
public:
    bool start();
    void stop();
    void restart();
    void setToneOn(bool isToneOn);
    Oscillator oscillator;
    AAudioStream *stream;
};

#endif //COMP696_LIGHT_SENSOR_AUDIOENGINE_H
