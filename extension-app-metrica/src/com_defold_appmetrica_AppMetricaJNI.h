#if defined(DM_PLATFORM_ANDROID)

#include <jni.h>

#ifndef COM_DEFOLD_APPMETRICA_APPMETRICAJNI_H
#define COM_DEFOLD_APPMETRICA_APPMETRICAJNI_H
#ifdef __cplusplus
extern "C" {
#endif
	
	JNIEXPORT void JNICALL Java_com_defold_appmetrica_AppMetricaJNI_AddToQueue
		(JNIEnv *, jclass, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif

#endif
