//
// Created by Kenvi Zhu on 2022-01-14.
//
#include <stdlib.h>
#include "wasmedge/wasmedge.h"
#include "common.h"
#include "MemoryTypeContext.h"


JNIEXPORT jlong JNICALL Java_org_wasmedge_MemoryInstanceContext_nativeInit
        (JNIEnv * env, jobject thisObject, jlong memoryTypePointer) {
    WasmEdge_MemoryTypeContext *memoryTypeContext = (WasmEdge_MemoryTypeContext *)memoryTypePointer;
    WasmEdge_MemoryInstanceContext *memInstance = WasmEdge_MemoryInstanceCreate(memoryTypeContext);
    return (jlong)memInstance;
}

JNIEXPORT void JNICALL Java_org_wasmedge_MemoryInstanceContext_nativeSetData
        (JNIEnv *env, jobject thisObject, jlong memoryInstancePointer, jbyteArray jData, jint jOffSet, jint jLength) {
    WasmEdge_MemoryInstanceContext *memoryInstanceContext = (WasmEdge_MemoryInstanceContext *)memoryInstancePointer;

    jbyte * buff = (*env)->GetByteArrayElements(env, jData, NULL);

    WasmEdge_MemoryInstanceSetData(memoryInstanceContext, (uint8_t *)buff, jOffSet, jLength);

    (*env)->ReleaseByteArrayElements(env, jData, buff, 0);
}


JNIEXPORT jbyteArray JNICALL Java_org_wasmedge_MemoryInstanceContext_nativeGetData
        (JNIEnv * env, jobject thisObject, jlong memoryInstancePointer, jint jOffSet, jint jSize) {
    WasmEdge_MemoryInstanceContext *memoryInstanceContext = (WasmEdge_MemoryInstanceContext *)memoryInstancePointer;
    uint8_t *data = (uint8_t*)malloc(sizeof(uint8_t) * jSize);

    WasmEdge_Result result = WasmEdge_MemoryInstanceGetData(memoryInstanceContext, data, jOffSet, jSize);
    if(!WasmEdge_ResultOK(result)) {
        free(data);
        return NULL;
    }
    handleWasmEdgeResult(env, &result);

    jbyteArray jBytes = (*env)->NewByteArray(env, jSize);
    (*env)->SetByteArrayRegion(env, jBytes, 0, jSize, (jbyte *)data);

    free(data);
    return jBytes;
}

JNIEXPORT jint JNICALL Java_org_wasmedge_MemoryInstanceContext_nativeGetPageSize
        (JNIEnv * env, jobject thisObject, jlong memoryInstancePointer) {
    WasmEdge_MemoryInstanceContext * memInstance = (WasmEdge_MemoryInstanceContext *)memoryInstancePointer;
    return WasmEdge_MemoryInstanceGetPageSize(memInstance);
}

JNIEXPORT void JNICALL Java_org_wasmedge_MemoryInstanceContext_nativeGrowPage
        (JNIEnv *env , jobject thisObject, jlong memoryInstancePointer, jint jSize) {
    WasmEdge_MemoryInstanceContext * memInstance = (WasmEdge_MemoryInstanceContext *)memoryInstancePointer;
    WasmEdge_Result result = WasmEdge_MemoryInstanceGrowPage(memInstance, jSize);
    handleWasmEdgeResult(env, &result);
}

JNIEXPORT void JNICALL Java_org_wasmedge_MemoryInstanceContext_nativeDelete
        (JNIEnv * env, jobject thisObject, jlong memoryInstancePointer) {
    WasmEdge_MemoryInstanceContext *memInstance = (WasmEdge_MemoryInstanceContext *)memoryInstancePointer;
    WasmEdge_MemoryInstanceDelete(memInstance);
}


jobject createJMemoryInstanceContext(JNIEnv* env, const WasmEdge_MemoryInstanceContext * memInstance) {

    // FIXME add to all instances.
    if(memInstance == NULL) {
        return NULL;
    }

    jclass clazz = (*env)->FindClass(env, "org/wasmedge/MemoryInstanceContext");
    jmethodID constructorId = (*env)->GetMethodID(env, clazz, "<init>", "(J)V");
    return (*env)->NewObject(env, clazz, constructorId, (long) memInstance);
}

