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

WasmEdge_Result HostFuncWrap(void *This, void* Data, WasmEdge_MemoryInstanceContext * Mem,
                         const WasmEdge_Value *In, const uint32_t InLen, WasmEdge_Value *Out, const uint32_t OutLen) {

    HostFuncParam * param = (HostFuncParam*)This;
    JNIEnv * env = param->env;
    const char* funcKey = param->jFuncKey;

    jstring jFuncKey = (*env)->NewStringUTF(env, funcKey);

    jclass clazz = (*env)->FindClass(env, "org/wasmedge/WasmEdgeVM");
    jmethodID funcGetter = (*env)->GetStaticMethodID(env, clazz, "getHostFunc", "(Ljava/lang/String;)Lorg/wasmedge/HostFunction;");
    if(checkException(env, "Error looking up getHostFunc")) {
        return WasmEdge_Result_Fail;
    }

    jobject jFunc = (*env)->CallStaticObjectMethod(env, clazz, funcGetter, jFuncKey);
    if(checkException(env, "Error calling getHostFunc")) {
        return WasmEdge_Result_Fail;
    }

    jclass jFuncClass = (*env)->GetObjectClass(env, jFunc);
    if(checkException(env, "Error looking up HostFunc class")) {
        return WasmEdge_Result_Fail;
    }

    jmethodID funcMethod = (*env)->GetMethodID(env, jFuncClass, "apply", "(Lorg/wasmedge/MemoryInstanceContext;Ljava/util/List;Ljava/util/List;)Lorg/wasmedge/Result;");
    if(checkException(env, "Error looking up apply method")) {
        return WasmEdge_Result_Fail;
    }

    jobject jMem = createJMemoryInstanceContext(env, Mem);

    jobject jParams = CreateJavaArrayList(env, InLen);

    for (int i = 0; i < InLen; ++i) {
        AddElementToJavaList(env, jParams, WasmEdgeValueToJavaValue(env, In[i]));
    }

    jobject jReturns = CreateJavaArrayList(env, OutLen);

    jobject result = (*env)->CallObjectMethod(env, jFunc, funcMethod, jMem, jParams, jReturns);
    if(checkException(env, "Error calling HostFunction.apply()")) {
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
        (JNIEnv *env, jobject thisObject, jlong funcTypePointer, jstring jHostFuncKey, jobject jData, jlong jCost) {
    WasmEdge_FunctionTypeContext *funcType = (WasmEdge_FunctionTypeContext *)funcTypePointer;

	// TODO Where do params and funcKey get freed?  We have no control over this currently
    HostFuncParam *params = malloc(sizeof(struct HostFuncParam));
    const char *funcKey = JStringToCString(env, jHostFuncKey);
    params->jFuncKey= funcKey;
    params->env = env;
 
    WasmEdge_FunctionInstanceContext *funcInstance = WasmEdge_FunctionInstanceCreateBinding(funcType, HostFuncWrap, params, NULL, jCost);

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
