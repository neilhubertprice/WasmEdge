//
// Created by Kenvi Zhu on 2022-03-14.
//
#include <stdlib.h>
#include "wasmedge/wasmedge.h"
#include "jni.h"
#include "common.h"
#include "FunctionTypeContext.h"
#include "FunctionTypeInstance.h"
#include "MemoryInstanceContext.h"
#include "ValueType.h"

WasmEdge_Result HostFuncWrap(void *This, void* Data, WasmEdge_MemoryInstanceContext *Mem,
                         const WasmEdge_Value *In, const uint32_t InLen, WasmEdge_Value *Out, const uint32_t OutLen) {
    JNIEnv *env = This;
    long funcKey = (long)Data;

    jclass clazz = (*env)->FindClass(env, "org/wasmedge/FunctionInstanceContext");

    jmethodID funcCallHF = (*env)->GetStaticMethodID(env, clazz, "callHostFunction", "(JJLjava/util/List;Ljava/util/List;)Lorg/wasmedge/Result;");
    if(checkException(env, "Error looking up callHostFunction")) {
        return WasmEdge_Result_Fail;
    }

    jobject jParams = construct_ArrayList(env, InLen);

    for (int i = 0; i < InLen; ++i) {
        jobject jValue = WasmEdgeValueToJavaValue(env, In[i]);
        call_List_add(env, jParams, jValue);
        (*env)->DeleteLocalRef(env, jValue);
    }

    jobject jReturns = construct_ArrayList(env, OutLen);

    jobject result = call_FunctionInstanceContext_static_callHostFunction(env, funcKey, (jlong)Mem, jParams, jReturns);

    jboolean isSuccess = true;
    jboolean isTerminate = false;

    if (result != NULL) {
        isSuccess = call_Result_isSuccess(env, result);
        isTerminate = call_Result_isTerminate(env, result);
    }

    if (isSuccess) {         
        // Only translate return values on success
        for (int i = 0; i < OutLen; ++i) {
            jobject jValue = call_List_get(env, jReturns, i);
            Out[i] = JavaValueToWasmEdgeValue(env, jValue);
            (*env)->DeleteLocalRef(env, jValue);
        }
    } else {
        return WasmEdge_Result_Fail;
    }

    if (isTerminate) {
        return WasmEdge_Result_Terminate;
    } else { 
        return WasmEdge_Result_Success;
    }
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_FunctionInstanceContext_nativeGetFunctionType
        (JNIEnv *env, jobject thisObject, jlong funcInstancePointer) {
    WasmEdge_FunctionInstanceContext *funcInstance = (WasmEdge_FunctionInstanceContext *)funcInstancePointer;
    const WasmEdge_FunctionTypeContext *funcType = WasmEdge_FunctionInstanceGetFunctionType(funcInstance);
    return (jlong)funcType;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_FunctionInstanceContext_nativeCreateFunction
        (JNIEnv *env, jobject thisObject, jlong funcTypePointer, jlong funcKey, jlong jCost) {
    WasmEdge_FunctionTypeContext *funcType = (WasmEdge_FunctionTypeContext *)funcTypePointer;
    WasmEdge_FunctionInstanceContext *funcInstance = WasmEdge_FunctionInstanceCreateBinding(funcType, HostFuncWrap, env, (void *)funcKey, jCost);

    return (jlong)funcInstance;
}

JNIEXPORT void JNICALL Java_org_wasmedge_FunctionInstanceContext_nativeDelete(JNIEnv *env, jobject thisObject, jlong funcInstancePointer) {
    WasmEdge_FunctionInstanceContext *funcInstance = (WasmEdge_FunctionInstanceContext *)funcInstancePointer;

    if (funcInstance != NULL) {
        WasmEdge_FunctionInstanceDelete(funcInstance);
    }
}

uint32_t GetReturnLen(WasmEdge_FunctionInstanceContext* functionInstanceContext) {
    const WasmEdge_FunctionTypeContext *type = WasmEdge_FunctionInstanceGetFunctionType(functionInstanceContext);
    return WasmEdge_FunctionTypeGetReturnsLength(type);
}
