/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_wasmedge_GlobalTypeContext */

#ifndef _Included_org_wasmedge_GlobalTypeContext
#define _Included_org_wasmedge_GlobalTypeContext
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_wasmedge_GlobalTypeContext
 * Method:    nativeInit
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_GlobalTypeContext_nativeInit
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     org_wasmedge_GlobalTypeContext
 * Method:    delete
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_GlobalTypeContext_delete
  (JNIEnv *, jobject);

/*
 * Class:     org_wasmedge_GlobalTypeContext
 * Method:    nativeGetValueType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_wasmedge_GlobalTypeContext_nativeGetValueType
  (JNIEnv *, jobject);

/*
 * Class:     org_wasmedge_GlobalTypeContext
 * Method:    nativeGetMutability
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_wasmedge_GlobalTypeContext_nativeGetMutability
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
