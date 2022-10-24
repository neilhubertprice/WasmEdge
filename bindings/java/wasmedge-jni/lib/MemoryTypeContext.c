//
// Created by Kenvi Zhu on 2022-01-14.
//
#include "wasmedge/wasmedge.h"
#include "common.h"


JNIEXPORT jlong JNICALL Java_org_wasmedge_MemoryTypeContext_nativeInit
        (JNIEnv *env, jobject thisObject, jboolean jHasMax, jlong jMin, jlong jMax) {
    const WasmEdge_Limit limit = {.HasMax = jHasMax, .Min = jMin, .Max = jMax};

    WasmEdge_MemoryTypeContext* memCxt = WasmEdge_MemoryTypeCreate(limit);

    return (jlong)memCxt;
}

JNIEXPORT void JNICALL Java_org_wasmedge_MemoryTypeContext_nativeDelete
        (JNIEnv *env, jobject thisObject, jlong memoryTypePointer) {
    WasmEdge_MemoryTypeContext *memoryTypeContext = (WasmEdge_MemoryTypeContext *)memoryTypePointer;
    WasmEdge_MemoryTypeDelete(memoryTypeContext);
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_MemoryTypeContext_nativeGetLimit
        (JNIEnv *env, jobject thisObject, jlong memoryTypePointer) {
    WasmEdge_MemoryTypeContext * memoryTypeContext = (WasmEdge_MemoryTypeContext *)memoryTypePointer;
    WasmEdge_Limit limit = WasmEdge_MemoryTypeGetLimit(memoryTypeContext);

    jclass limitClass = findJavaClass(env, "org/wasmedge/WasmEdgeLimit");

    jmethodID constructor = findJavaMethod(env, limitClass, "<init>", "(ZJJ)V");

    return (*env)->NewObject(env, limitClass, constructor,
                             (jboolean)limit.HasMax, (jlong)limit.Min, (jlong)limit.Max);
}
