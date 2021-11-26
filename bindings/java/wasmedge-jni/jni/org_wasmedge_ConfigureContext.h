/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_wasmedge_ConfigureContext */

#ifndef _Included_org_wasmedge_ConfigureContext
#define _Included_org_wasmedge_ConfigureContext
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_wasmedge_ConfigureContext
 * Method:    nativeInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeInit
  (JNIEnv *, jobject);

/*
 * Class:     org_wasmedge_ConfigureContext
 * Method:    cleanUp
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_delete
  (JNIEnv *, jobject);

/*
 * Class:     org_wasmedge_ConfigureContext
 * Method:    addHostRegistration
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_addHostRegistration
  (JNIEnv *, jobject);

/*
 * Class:     org_wasmedge_ConfigureContext
 * Method:    setMaxMemoryPage
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_setMaxMemoryPage
  (JNIEnv *, jobject, jlong);

/*
 * Class:     org_wasmedge_ConfigureContext
 * Method:    setStatisticsSetInstructionCounting
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_setStatisticsSetInstructionCounting
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     org_wasmedge_ConfigureContext
 * Method:    setStatisticsSetCostMeasuring
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_setStatisticsSetCostMeasuring
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     org_wasmedge_ConfigureContext
 * Method:    setStatisticsSetTimeMeasuring
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_setStatisticsSetTimeMeasuring
  (JNIEnv *, jobject, jboolean);

#ifdef __cplusplus
}
#endif
#endif
