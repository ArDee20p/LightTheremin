#include <jni.h>
#include <android/input.h>
#include <android/log.h>
#include "AudioEngine.h"

#define _UN_ __attribute__((unused))

AudioEngine *audioEngine = new AudioEngine();

extern "C" {

    JNIEXPORT void JNICALL
    Java_de_vogella_android_lightsensor_MainActivity_onSensorEvent(JNIEnv *env _UN_, jobject obj _UN_, jfloat sensor_value, jchar mode) {
        audioEngine->restart(); //TODO: this is a kludge-y method to get the tone output to update, and it results in hitches in the sound output. any better way to do this?
        audioEngine->oscillator.setFrequency(sensor_value, mode);

        __android_log_print(ANDROID_LOG_DEBUG, "SOUND", "Tone: %f Hz", sensor_value);
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
