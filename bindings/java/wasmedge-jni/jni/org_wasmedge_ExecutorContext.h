/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_wasmedge_ExecutorContext */

#ifndef _Included_org_wasmedge_ExecutorContext
#define _Included_org_wasmedge_ExecutorContext
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_wasmedge_ExecutorContext
 * Method:    nativeInit
 * Signature: (Lorg/wasmedge/ConfigureContext;Lorg/wasmedge/StatisticsContext;)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeInit
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     org_wasmedge_ExecutorContext
 * Method:    instantiate
 * Signature: (Lorg/wasmedge/StoreContext;Lorg/wasmedge/ASTModuleContext;)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_instantiate
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     org_wasmedge_ExecutorContext
 * Method:    invoke
 * Signature: (Lorg/wasmedge/StoreContext;Ljava/lang/String;[Lorg/wasmedge/WasmEdgeValue;[I[Lorg/wasmedge/WasmEdgeValue;[I)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_invoke
  (JNIEnv *, jobject, jobject, jstring, jobjectArray, jintArray, jobjectArray, jintArray);

/*
 * Class:     org_wasmedge_ExecutorContext
 * Method:    invokeRegistered
 * Signature: (Lorg/wasmedge/StoreContext;Ljava/lang/String;Ljava/lang/String;[Lorg/wasmedge/WasmEdgeValue;[I[Lorg/wasmedge/WasmEdgeValue;[I)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_invokeRegistered
  (JNIEnv *, jobject, jobject, jstring, jstring, jobjectArray, jintArray, jobjectArray, jintArray);

/*
 * Class:     org_wasmedge_ExecutorContext
 * Method:    registerModule
 * Signature: (Lorg/wasmedge/StoreContext;Lorg/wasmedge/ASTModuleContext;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_registerModule
  (JNIEnv *, jobject, jobject, jobject, jstring);

/*
 * Class:     org_wasmedge_ExecutorContext
 * Method:    registerImport
 * Signature: (Lorg/wasmedge/StoreContext;Lorg/wasmedge/ImportTypeContext;)V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_registerImport
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     org_wasmedge_ExecutorContext
 * Method:    delete
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_delete
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
