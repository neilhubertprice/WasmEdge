//
// Created by Kenvi Zhu on 2021-12-08.
//

#include "wasmedge/wasmedge.h"
#include "common.h"


JNIEXPORT jlong JNICALL Java_org_wasmedge_TableTypeContext_nativeInit
        (JNIEnv *env, jobject thisObject, jint refType, jboolean jHasMax, jlong jMin, jlong jMax) {
    WasmEdge_Limit tableLimit = {.HasMax = jHasMax, .Min = jMin, .Max = jMax};
    WasmEdge_TableTypeContext * tableTypeContext = WasmEdge_TableTypeCreate((enum WasmEdge_RefType) refType, tableLimit);
    return (jlong)tableTypeContext;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_TableTypeContext_nativeGetLimit
        (JNIEnv *env, jobject thisObject, jlong tableTypePointer) {
    WasmEdge_TableTypeContext *tableTypeContext = (WasmEdge_TableTypeContext *)tableTypePointer;

    WasmEdge_Limit limit = WasmEdge_TableTypeGetLimit(tableTypeContext);

    return construct_WasmEdgeLimit(env, (jboolean)limit.HasMax, (jlong)limit.Min, (jlong)limit.Max);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_TableTypeContext_nativeGetRefType
        (JNIEnv *env, jobject thisObject, jlong tableTypePointer) {
    WasmEdge_TableTypeContext *tableTypeContext = (WasmEdge_TableTypeContext *)tableTypePointer;

    return WasmEdge_TableTypeGetRefType(tableTypeContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_TableTypeContext_nativeDelete
        (JNIEnv *env, jobject thisObject, jlong tableTypePointer) {
    WasmEdge_TableTypeContext *tableTypeContext = (WasmEdge_TableTypeContext *)tableTypePointer;
    WasmEdge_TableTypeDelete(tableTypeContext);
}
