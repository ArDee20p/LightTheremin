#include <jni.h>
#include <android/input.h>
#include <android/log.h>
#include "AudioEngine.h"

static AudioEngine *audioEngine = new AudioEngine();

extern "C" {

    JNIEXPORT void JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_onSensorEvent(JNIEnv *env, jobject obj,
                                                                   jfloat sensor_value) {
        audioEngine->restart(); //TODO: this is a kludge-y method to get the tone output to update, and it results in hitches in the sound output. any better way to do this?
        audioEngine->oscillator.setFrequency(sensor_value);

        __android_log_print(ANDROID_LOG_DEBUG, "SOUND", "Tone: %f Hz", sensor_value);
    }

    JNIEXPORT void JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_startEngine(JNIEnv *env, jobject /* this */) {
        audioEngine->start();
        audioEngine->setToneOn(true);
    }

    JNIEXPORT void JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_stopEngine(JNIEnv *env, jobject /* this */) {
        audioEngine->stop();
        audioEngine->setToneOn(false);
    }

    JNIEXPORT void JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_restartEngine(JNIEnv *env, jobject /* this */) {
        audioEngine->restart();
        audioEngine->setToneOn(true);
    }
}
