//
// Created by Kenvi Zhu on 2022-01-13.
//
#include "wasmedge/wasmedge.h"
#include "jni.h"
#include "common.h"

WasmEdge_Value JavaValueToWasmEdgeValue(JNIEnv *env, jobject jVal) {
    jobject valType = call_WasmEdgeValue_getType(env, jVal);
    jint jType = call_ValueType_getValue(env, valType);
    enum WasmEdge_ValType type = (enum WasmEdge_ValType)jType;

    WasmEdge_Value val;

    switch (type) {
        case WasmEdge_ValType_I32:
            return WasmEdge_ValueGenI32(call_WasmEdgeI32Value_getValue(env, jVal));
        case WasmEdge_ValType_I64:
            return WasmEdge_ValueGenI64(call_WasmEdgeI64Value_getValue(env, jVal));
        case WasmEdge_ValType_F32:
            return WasmEdge_ValueGenF32(call_WasmEdgeF32Value_getValue(env, jVal));
        case WasmEdge_ValType_F64:
            return WasmEdge_ValueGenF64(call_WasmEdgeF64Value_getValue(env, jVal));
        case WasmEdge_ValType_V128:
            //TODO
            return WasmEdge_ValueGenV128(call_WasmEdgeI64Value_getValue(env, jVal));
        case WasmEdge_ValType_ExternRef:
            return WasmEdge_ValueGenExternRef(getExternRefStringVal(env, jVal));

        case WasmEdge_ValType_FuncRef:
            // TODO
            return WasmEdge_ValueGenFuncRef(call_WasmEdgeI64Value_getValue(env, jVal));
    }
}

jobject WasmEdgeValueToJavaValue(JNIEnv *env, WasmEdge_Value value) {
    jobject jVal;
    switch (value.Type) {
        case WasmEdge_ValType_I32:
            jVal = construct_WasmEdgeI32Value_withParam(env, WasmEdge_ValueGetI32(value));
            break;
        case WasmEdge_ValType_I64:
            jVal = construct_WasmEdgeI64Value_withParam(env, WasmEdge_ValueGetI64(value));
            break;
        case WasmEdge_ValType_F32:
            jVal = construct_WasmEdgeF32Value_withParam(env, WasmEdge_ValueGetF32(value));
            break;
        case WasmEdge_ValType_F64:
            jVal = construct_WasmEdgeF64Value_withParam(env, WasmEdge_ValueGetF64(value));
            break;
        case WasmEdge_ValType_V128:
            // TODO
            jVal = NULL;
            break;
        case WasmEdge_ValType_ExternRef:
            jVal = construct_WasmEdgeExternRef(env);
            setExternRefStringVal(env, value, jVal);
            break;
        case WasmEdge_ValType_FuncRef:
            // TODO
            jVal = NULL;
            break;
    }

    return jVal;
}

