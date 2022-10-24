//
// Created by Kenvi Zhu on 2022-01-12.
//

#include "common.h"
#include "GlobalTypeContext.h"
#include "ValueType.h"


JNIEXPORT jlong JNICALL Java_org_wasmedge_GlobalInstanceContext_nativeInit
        (JNIEnv * env, jobject thisObject, jlong globalTypePointer, jobject jVal) {
    WasmEdge_GlobalTypeContext *globalTypeContext = (WasmEdge_GlobalTypeContext *)globalTypePointer;

    WasmEdge_GlobalInstanceContext *globalInstanceContext =
            WasmEdge_GlobalInstanceCreate(globalTypeContext, JavaValueToWasmEdgeValue(env, jVal));
    return (jlong)globalInstanceContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_GlobalInstanceContext_nativeSetValue
        (JNIEnv *env, jobject thisObject, jlong globalInstancePointer, jobject jVal) {
    WasmEdge_GlobalInstanceContext *globalInstanceContext = (WasmEdge_GlobalInstanceContext *)globalInstancePointer;

    WasmEdge_Value value = JavaValueToWasmEdgeValue(env, jVal);

    WasmEdge_GlobalInstanceSetValue(globalInstanceContext, value);
}

JNIEXPORT void JNICALL Java_org_wasmedge_GlobalInstanceContext_nativeDelete
        (JNIEnv *env, jobject thisObject, jlong globalInstancePointer) {
    WasmEdge_GlobalInstanceContext * globalInstanceContext = (WasmEdge_GlobalInstanceContext *)globalInstancePointer;
    WasmEdge_GlobalInstanceDelete(globalInstanceContext);
}

