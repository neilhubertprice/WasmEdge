//
// Created by Kenvi Zhu on 2022-01-14.
//
#include "wasmedge/wasmedge.h"
#include "TableTypeContext.h"
#include "common.h"
#include "ValueType.h"


JNIEXPORT jlong JNICALL Java_org_wasmedge_TableInstanceContext_nativeInit
        (JNIEnv * env, jobject thisObject, jlong tableTypePointer) {
    WasmEdge_TableTypeContext *tableTypeContext = (WasmEdge_TableTypeContext *)tableTypePointer;
    WasmEdge_TableInstanceContext *tableInstanceContext = WasmEdge_TableInstanceCreate(tableTypeContext);
    return (jlong)tableInstanceContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_TableInstanceContext_nativeDelete
        (JNIEnv * env, jobject thisObject, jlong tableInstancePointer) {
    WasmEdge_TableInstanceContext *tableInstanceContext = (WasmEdge_TableInstanceContext *)tableInstancePointer;
    WasmEdge_TableInstanceDelete(tableInstanceContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_TableInstanceContext_nativeSetData
        (JNIEnv * env, jobject thisObject, jlong tableInstancePointer, jobject jVal, jint jOffSet) {
    WasmEdge_TableInstanceContext *tableInstanceContext = (WasmEdge_TableInstanceContext *)tableInstancePointer;
    WasmEdge_Value data = JavaValueToWasmEdgeValue(env, jVal);
    WasmEdge_Result result = WasmEdge_TableInstanceSetData(tableInstanceContext, data, jOffSet);
    handleWasmEdgeResult(env, &result);
}


JNIEXPORT jobject JNICALL Java_org_wasmedge_TableInstanceContext_nativeGetData
        (JNIEnv * env, jobject thisObject, jlong tableInstancePointer, jobject jValType, jint jOffSet) {
    WasmEdge_TableInstanceContext *tableInstanceContext = (WasmEdge_TableInstanceContext *)tableInstancePointer;
    jint valType = call_ValueType_getValue(env, jValType);

    WasmEdge_Value val;

    switch (valType) {
        case WasmEdge_ValType_I32:
            val = WasmEdge_ValueGenI32(0);
            break;
        case WasmEdge_ValType_I64:
            val = WasmEdge_ValueGenF64(0);
            break;
        case WasmEdge_ValType_F32:
            val = WasmEdge_ValueGenF32(0.0);
            break;
        case WasmEdge_ValType_F64:
            val = WasmEdge_ValueGenF64(0.0);
            break;
        case WasmEdge_ValType_FuncRef:
            val = WasmEdge_ValueGenNullRef(WasmEdge_RefType_FuncRef);
            break;
        case WasmEdge_ValType_ExternRef:
            val = WasmEdge_ValueGenNullRef(WasmEdge_RefType_ExternRef);
            break;
    }

    WasmEdge_TableInstanceGetData(tableInstanceContext, &val, jOffSet);
    return WasmEdgeValueToJavaValue(env, val);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_TableInstanceContext_nativeGetSize
        (JNIEnv * env, jobject thisObject, jlong tableInstancePointer) {
    WasmEdge_TableInstanceContext *tableInstanceContext = (WasmEdge_TableInstanceContext *)tableInstancePointer;
    return WasmEdge_TableInstanceGetSize(tableInstanceContext);
}


JNIEXPORT void JNICALL Java_org_wasmedge_TableInstanceContext_nativeGrow
        (JNIEnv * env, jobject thisObject, jlong tableInstancePointer, jint jSize) {
    WasmEdge_TableInstanceContext *tableInstanceContext = (WasmEdge_TableInstanceContext *)tableInstancePointer;
    WasmEdge_Result result = WasmEdge_TableInstanceGrow(tableInstanceContext, jSize);
    handleWasmEdgeResult(env, &result);
}

