#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>
#include "appmetrica_private.h"
#include "com_defold_appmetrica_AppMetricaJNI.h"
#include "appmetrica_callback_private.h"

JNIEXPORT void JNICALL Java_com_defold_appmetrica_AppMetricaJNI_AddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmAppMetrica::AddToQueueCallback((dmAppMetrica::MessageId)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}

namespace dmAppMetrica {

struct AppMetrica
{
    jobject        m_AppMetricaJNI;

    jmethodID      m_Initialize;

};

static AppMetrica       g_appMetrica;

static void CallVoidMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method);
}

static bool CallBoolMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jboolean return_value = (jboolean)env->CallBooleanMethod(instance, method);
    return JNI_TRUE == return_value;
}

static void CallVoidMethodChar(jobject instance, jmethodID method, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr);
    env->DeleteLocalRef(jstr);
}

static void CallVoidMethodCharInt(jobject instance, jmethodID method, const char* cstr, int cint)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr, cint);
    env->DeleteLocalRef(jstr);
}

static void CallVoidMethodInt(jobject instance, jmethodID method, int cint)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method, cint);
}

static void CallVoidMethodBool(jobject instance, jmethodID method, bool cbool)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method, cbool);
}

static void InitJNIMethods(JNIEnv* env, jclass cls)
{
    g_appMetrica.m_Initialize = env->GetMethodID(cls, "initialize", "(Ljava/lang/String;)V");
}

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.appmetrica.AppMetricaJNI");

    InitJNIMethods(env, cls);

    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");

    g_appMetrica.m_AppMetricaJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

void Initialize(const char* unitId)
{
     CallVoidMethodChar(g_appMetrica.m_AppMetricaJNI, g_appMetrica.m_Initialize, unitId);
}

void ActivateApp()
{
    //
}

}//namespace dmAppMetrica

#endif
