//
// Created by Kenvi Zhu on 2021-12-07.
//

#include "wasmedge/wasmedge.h"
#include "common.h"


JNIEXPORT jlong JNICALL Java_org_wasmedge_GlobalTypeContext_nativeInit
        (JNIEnv * env, jobject thisObject, jint valueType, jint mutability) {
    WasmEdge_GlobalTypeContext *globalTypeContext  =
            WasmEdge_GlobalTypeCreate((enum WasmEdge_ValType)valueType, (enum WasmEdge_Mutability) mutability);
    return (jlong)globalTypeContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_GlobalTypeContext_nativeDelete
        (JNIEnv *env, jobject thisObject, jlong globalTypePointer) {
    WasmEdge_GlobalTypeContext *globalTypeContext = (WasmEdge_GlobalTypeContext *)globalTypePointer;
    WasmEdge_GlobalTypeDelete(globalTypeContext);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_GlobalTypeContext_nativeGetValueType
        (JNIEnv * env, jobject thisObject, jlong globalTypePointer) {
    WasmEdge_GlobalTypeContext *globalTypeContext = (WasmEdge_GlobalTypeContext *)globalTypePointer;
    return WasmEdge_GlobalTypeGetValType(globalTypeContext);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_GlobalTypeContext_nativeGetMutability
        (JNIEnv * env, jobject thisObject, jlong globalTypePointer) {
    WasmEdge_GlobalTypeContext *globalTypeContext = (WasmEdge_GlobalTypeContext *)globalTypePointer;
    return WasmEdge_GlobalTypeGetMutability(globalTypeContext);
}
