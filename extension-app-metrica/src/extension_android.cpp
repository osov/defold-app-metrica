#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>
#include "extension_private.h"
#include "com_defold_extension_ExtensionAppMetrica.h"
#include "extension_callback_private.h"

JNIEXPORT void JNICALL Java_com_defold_extension_ExtensionAppMetrica_AddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmAppMetrica::AddToQueueCallback((dmAppMetrica::MessageId)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}

namespace dmAppMetrica {

struct App
{
    jobject    m_AppJNI;
    jmethodID  m_Initialize;
    jmethodID  m_ReportEvent;
    jmethodID  m_SendRevenue;
};

static App       g_app;

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

static void CallVoidMethodCharChar(jobject instance, jmethodID method, const char* cstr1, const char* cstr2)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr1 = env->NewStringUTF(cstr1);
    jstring jstr2 = env->NewStringUTF(cstr2);
    env->CallVoidMethod(instance, method, jstr1, jstr2);
    env->DeleteLocalRef(jstr1);
    env->DeleteLocalRef(jstr2);
}

static void CallVoidMethodCharCharCharCharChar(jobject instance, jmethodID method, const char* cstr1, const char* cstr2, const char* cstr3, const char* cstr4, const char* cstr5)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr1 = env->NewStringUTF(cstr1);
    jstring jstr2 = env->NewStringUTF(cstr2);
    jstring jstr3 = env->NewStringUTF(cstr3);
    jstring jstr4 = env->NewStringUTF(cstr4);
    jstring jstr5 = env->NewStringUTF(cstr5);
    env->CallVoidMethod(instance, method, jstr1, jstr2, jstr3, jstr4, jstr5);
    env->DeleteLocalRef(jstr1);
    env->DeleteLocalRef(jstr2);
    env->DeleteLocalRef(jstr3);
    env->DeleteLocalRef(jstr4);
    env->DeleteLocalRef(jstr5);
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
    g_app.m_Initialize = env->GetMethodID(cls, "initialize", "(Ljava/lang/String;)V");
    g_app.m_ReportEvent = env->GetMethodID(cls, "ReportEvent", "(Ljava/lang/String;Ljava/lang/String;)V");
    g_app.m_SendRevenue = env->GetMethodID(cls, "SendRevenue", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
}

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.extension.ExtensionAppMetrica");

    InitJNIMethods(env, cls);

    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");

    g_app.m_AppJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

void Initialize(const char* unitId)
{
     CallVoidMethodChar(g_app.m_AppJNI, g_app.m_Initialize, unitId);
}

void ReportEvent(const char* s1, const char* s2)
{
    CallVoidMethodCharChar(g_app.m_AppJNI, g_app.m_ReportEvent, s1, s2);
}

void SendRevenue(const char* s1, const char* s2, const char* s3, const char* s4, const char* s5)
{
    CallVoidMethodCharCharCharCharChar(g_app.m_AppJNI, g_app.m_SendRevenue, s1, s2, s3, s4, s5);
}

void ActivateApp()
{
    //
}

}

#endif
