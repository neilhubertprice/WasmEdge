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

    jobject jParams = CreateJavaArrayList(env, InLen);

    for (int i = 0; i < InLen; ++i) {
        AddElementToJavaList(env, jParams, WasmEdgeValueToJavaValue(env, In[i]));
    }

    jobject jReturns = CreateJavaArrayList(env, OutLen);

    jobject result = (*env)->CallStaticObjectMethod(env, clazz, funcCallHF, funcKey, Mem, jParams, jReturns);
    if(checkException(env, "Error calling callHostFunction")) {
        return WasmEdge_Result_Fail;
    }

    for (int i = 0; i < OutLen; ++i) {
       Out[i] = JavaValueToWasmEdgeValue(env, GetListElement(env, jReturns, i));
    }

    jboolean isSuccess = true;
    jboolean isTerminate = false;

    if (result != NULL) {
        jclass resultClass = (*env)->GetObjectClass(env, result);
        if(checkException(env, "Error looking up Result class")) {
            return WasmEdge_Result_Fail;
        }
	    if (resultClass != NULL) {
            jmethodID resultSuccess = (*env)->GetMethodID(env, resultClass, "isSuccess", "()Z");
            if(checkException(env, "Error looking up isSuccess method")) {
                return WasmEdge_Result_Fail;
            }
            if (resultSuccess != NULL) {
                isSuccess = (*env)->CallBooleanMethod(env, result, resultSuccess);
                if(checkException(env, "Error calling isSuccess method")) {
                    return WasmEdge_Result_Fail;
                }

                jmethodID resultTerminate = (*env)->GetMethodID(env, resultClass, "isTerminate", "()Z");
                if(checkException(env, "Error looking up isTerminate method")) {
                    return WasmEdge_Result_Fail;
                }
                if (resultTerminate != NULL) {
                    isTerminate = (*env)->CallBooleanMethod(env, result, resultTerminate);
                    if(checkException(env, "Error calling isTerminate method")) {
                        return WasmEdge_Result_Fail;
                    }
                }
            }
        }
    }

    if (!isSuccess) {
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

// Not currently implemented
// JNIEXPORT jlong JNICALL Java_org_wasmedge_FunctionInstanceContext_nativeCreateBinding
//         (JNIEnv *env, jobject thisObject, jobject jWrapFuncType, jobject jWrapFunc, jobject jBinding, jobject jData, jlong jCost) {
// }

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
