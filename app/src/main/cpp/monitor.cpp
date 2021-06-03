#include <jni.h>
#include <string>
#include "jvmti.h"
#include "android/log.h"

jvmtiEnv *_jvmtiEnv;

/**
 * jvm 挂载 jvmti程序 就回调这个方法
 *
 * @param vm
 * @param options
 * @param reserved
 * @return
 */
JNIEXPORT jint JNICALL Agent_OnAttach(JavaVM *vm, char *options, void *reserved) {
    vm->GetEnv(reinterpret_cast<void **>(&_jvmtiEnv), JVMTI_VERSION_1_2);
    // 获取jvmti 能力
    jvmtiCapabilities capabilities;
    _jvmtiEnv->GetPotentialCapabilities(&capabilities);
    // 开启
    _jvmtiEnv->AddCapabilities(&capabilities);

    return JNI_OK;
}


void objectAlloc(jvmtiEnv *jvmti_env,
                 JNIEnv *jni_env,
                 jthread thread,
                 jobject object,
                 jclass object_klass,
                 jlong size) {
    __android_log_print(ANDROID_LOG_ERROR, "tag", ">>>>>>>>>>>>>>>>>>创建了对象");
}

void objectFree(jvmtiEnv *jvmti_env, jlong tag) {
    __android_log_print(ANDROID_LOG_ERROR, "tag", ">>>>>>>>>>>>>>>>>>对象被会回收了");
}


extern "C"
JNIEXPORT void JNICALL
Java_com_github_xapm_Monitor_native_1init(JNIEnv *env, jclass clazz, jstring path) {

    jvmtiEventCallbacks _jvmtiEventCallbacks;

    _jvmtiEventCallbacks.VMObjectAlloc = &objectAlloc;
    _jvmtiEventCallbacks.ObjectFree = &objectFree;

    // 注册监听
    _jvmtiEnv->SetEventCallbacks(&_jvmtiEventCallbacks, sizeof(_jvmtiEventCallbacks));


    //开启监听
    _jvmtiEnv->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_VM_OBJECT_ALLOC, NULL);
    _jvmtiEnv->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_OBJECT_FREE, NULL);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_github_xapm_Monitor_native_1release(JNIEnv *env, jclass clazz) {
    //关闭监听
    _jvmtiEnv->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_VM_OBJECT_ALLOC, NULL);
    _jvmtiEnv->SetEventNotificationMode(JVMTI_DISABLE, JVMTI_EVENT_OBJECT_FREE, NULL);
}
