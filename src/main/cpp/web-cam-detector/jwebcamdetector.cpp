#include "nkdhny_runtag_WebcamDetector.h"
#include "webcamdetector.h"
#include <iostream>

JNIEXPORT jlong JNICALL Java_nkdhny_runtag_WebcamDetector_setupNativeDetector
  (JNIEnv * env, jobject thiz) {
    jclass objectClass = env->GetObjectClass(thiz);

    jfieldID cameraFieldId = env->GetFieldID(objectClass, "cameraId", "I");
    int cameraId = static_cast<int>(env->GetIntField(thiz, cameraFieldId));

    nkdhny::WebcamDetector* detector = new nkdhny::WebcamDetector(static_cast<unsigned>(cameraId));

    jfieldID detectorFieldId = env->GetFieldID(objectClass, "nativeDetectorPointer", "J");

    std::cout<<(jlong)detector<<std::endl;

    env->SetLongField(thiz, detectorFieldId, (jlong)detector);
}

JNIEXPORT void JNICALL Java_nkdhny_runtag_WebcamDetector_releaseNativeDetector
  (JNIEnv * env, jobject thiz) {


    jclass objectClass = env->GetObjectClass(thiz);
    jfieldID detectorFieldId = env->GetFieldID(objectClass, "nativeDetectorPointer", "J");
    nkdhny::WebcamDetector* detector = (nkdhny::WebcamDetector*)env->GetLongField(thiz, detectorFieldId);

    delete detector;
}

static jobject createJavaTag(JNIEnv* env, jclass tagDefinition, nkdhny::Marker m, const cv::Size& imgSize) {
    static jmethodID tagConstructorDefinition = env->GetMethodID(tagDefinition, "<init>", "(JFF)V");
    assert(tagConstructorDefinition != NULL);

    return env->NewObject(
                tagDefinition,
                tagConstructorDefinition,
                m.id(), ((float)m.center().x/imgSize.width), ((float)m.center().y/imgSize.height));

}


JNIEXPORT jobjectArray JNICALL Java_nkdhny_runtag_WebcamDetector_apply
  (JNIEnv * env, jobject thiz) {

    jclass objectClass = env->GetObjectClass(thiz);
    jfieldID detectorFieldId = env->GetFieldID(objectClass, "nativeDetectorPointer", "J");
    nkdhny::WebcamDetector* detector = (nkdhny::WebcamDetector*)env->GetLongField(thiz, detectorFieldId);

    std::vector<nkdhny::Marker> markers = detector->apply();

    jclass tagDefinition = env->FindClass("nkdhny/runtag/Tag");
    jobjectArray ret = env->NewObjectArray(
                markers.size(), tagDefinition, createJavaTag(env, tagDefinition, nkdhny::Marker(), detector->getCaptureSize()));

    for(int i = 0; i< markers.size(); i++) {
        env->SetObjectArrayElement(ret, i, createJavaTag(env, tagDefinition, markers[i], detector->getCaptureSize()));
    }

    return ret;
}

