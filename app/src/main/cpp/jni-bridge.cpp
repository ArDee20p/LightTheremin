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

#include <jni.h>
#include <android/input.h>
#include <android/log.h>
#include "AudioEngine.h"

#define _UN_ __attribute__((unused))

AudioEngine *audioEngine = new AudioEngine();

extern "C" {

    JNIEXPORT jdouble JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_onSensorEvent(JNIEnv *env _UN_, jobject obj _UN_, jfloat sensor_value, jchar mode) {
        jdouble val;
        val = audioEngine->oscillator_->setFrequency(sensor_value, mode);
        //TODO: data callback not firing
        __android_log_print(ANDROID_LOG_DEBUG, "SOUND", "Tone: %f Hz", sensor_value);
        return val;
    }

    JNIEXPORT void JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_startEngine(JNIEnv *env _UN_, jobject thiz _UN_) {
        audioEngine->start();
    }

    JNIEXPORT void JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_stopEngine(JNIEnv *env _UN_, jobject thiz _UN_) {
        audioEngine->stop();
    }

    JNIEXPORT void JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_toneSet(JNIEnv *env _UN_, jobject thiz _UN_, jboolean do_sound) {
        audioEngine->setToneOn(do_sound);
    }
}
