//
// Created by Kenvi Zhu on 2022-01-09.
//
#include <stdlib.h>
#include "jni.h"
#include "wasmedge/wasmedge.h"
#include "StatisticsContext.h"
#include "ConfigureContext.h"
#include "common.h"
#include "AstModuleContext.h"
#include "StoreContext.h"
#include "ImportObjectContext.h"
#include "common.h"
#include "ValueType.h"
#include "FunctionTypeInstance.h"


JNIEXPORT jlong JNICALL Java_org_wasmedge_ExecutorContext_nativeInit
        (JNIEnv *env, jobject thisObject, jlong configContextPointer, jlong statContextPointer) {
    WasmEdge_ConfigureContext *confCxt = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_StatisticsContext *statCxt = (WasmEdge_StatisticsContext *)statContextPointer;

    WasmEdge_ExecutorContext *exeCxt = WasmEdge_ExecutorCreate(confCxt, statCxt);
    return (jlong)exeCxt;
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeInstantiate
        (JNIEnv *env, jobject thisObject, jlong executorContextPointer, jlong storeContextPointer, jlong astmContextPointer) {
    WasmEdge_ExecutorContext *exeCxt = (WasmEdge_ExecutorContext *)executorContextPointer;
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_ASTModuleContext *astModCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

    WasmEdge_ExecutorInstantiate(exeCxt, storeCxt, astModCxt);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeInvoke
        (JNIEnv *env, jobject thisObject, jlong executorContextPointer, jlong storeContextPointer, jstring jFuncName,
        jobject jParams, jobject jReturns) {
    WasmEdge_ExecutorContext *exeCxt = (WasmEdge_ExecutorContext *)executorContextPointer;
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    jsize paramLen = call_List_size(env, jParams);

    /* The parameters and returns arrays. */
    WasmEdge_Value *wasm_params = calloc(paramLen, sizeof(WasmEdge_Value));
    for (int i = 0; i < paramLen; i++) {
        jobject jValue = call_List_get(env, jParams, i);
        wasm_params[i] = JavaValueToWasmEdgeValue(env, jValue);
        (*env)->DeleteLocalRef(env, jValue);
    }

    uint32_t returnLen = GetReturnLen(WasmEdge_StoreFindFunction(storeCxt, wFuncName));
    WasmEdge_Value *returns = malloc(sizeof(WasmEdge_Value) * returnLen);

    WasmEdge_Result result = WasmEdge_ExecutorInvoke(exeCxt, storeCxt, wFuncName, wasm_params, paramLen, returns, returnLen);

    handleWasmEdgeResult(env, & result);

    if (WasmEdge_ResultOK(result)) {
        for (int i = 0; i < returnLen; ++i) {
            jobject jValue = WasmEdgeValueToJavaValue(env, returns[i]);
            call_List_add(env, jReturns, jValue);
            (*env)->DeleteLocalRef(env, jValue);
        }
    }

    //release resource
    free(wasm_params);
    free(returns);
    WasmEdge_StringDelete(wFuncName);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeInvokeRegistered
        (JNIEnv *env, jobject thisObject, jlong executorContextPointer, jlong storeContextPointer, jstring jModName,
        jstring jFuncName, jobject jParams, jobject jReturns) {
    WasmEdge_ExecutorContext * exeCxt = (WasmEdge_ExecutorContext *)executorContextPointer;
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    jsize paramLen = call_List_size(env, jParams);

    /* The parameters and returns arrays. */
    WasmEdge_Value *wasm_params = calloc(paramLen, sizeof(WasmEdge_Value));
    for (int i = 0; i < paramLen; i++) {
        jobject val_object = call_List_get(env, jParams, i);
        wasm_params[i] = JavaValueToWasmEdgeValue(env, val_object);
        (*env)->DeleteLocalRef(env, val_object);
    }

    jsize returnLen = call_List_size(env, jReturns);
    WasmEdge_Value *returns = malloc(sizeof(WasmEdge_Value) * returnLen);

    WasmEdge_Result result = WasmEdge_ExecutorInvokeRegistered(exeCxt, storeCxt, wModName, wFuncName, wasm_params, paramLen, returns, returnLen);

    handleWasmEdgeResult(env, & result);

    if (WasmEdge_ResultOK(result)) {
        for (int i = 0; i < returnLen; ++i) {
            jobject jValue = WasmEdgeValueToJavaValue(env, returns[i]);
            call_List_add(env, jReturns, jValue);
            (*env)->DeleteLocalRef(env, jValue);
        }
    }

    //release resource
    free(wasm_params);
    free(returns);
    WasmEdge_StringDelete(wFuncName);
    WasmEdge_StringDelete(wModName);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeRegisterModule
        (JNIEnv * env, jobject thisObject, jlong executorContextPointer, jlong storeContextPointer, jlong astmContextPointer, jstring jModName) {
    WasmEdge_ExecutorContext *exeCxt = (WasmEdge_ExecutorContext *)executorContextPointer;
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_ASTModuleContext *astModCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

    WasmEdge_String wModName = JStringToWasmString(env, jModName);

    WasmEdge_Result result = WasmEdge_ExecutorRegisterModule(exeCxt, storeCxt, astModCxt, wModName);

    handleWasmEdgeResult(env, &result);

    WasmEdge_StringDelete(wModName);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeRegisterImport
        (JNIEnv *env, jobject thisObject, jlong executorContextPointer, jlong storeContextPointer, jlong importObjectPointer) {
    WasmEdge_ExecutorContext *exeCxt = (WasmEdge_ExecutorContext *)executorContextPointer;
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_ImportObjectContext *impObj = (WasmEdge_ImportObjectContext *)importObjectPointer;

    WasmEdge_ExecutorRegisterImport(exeCxt, storeCxt, impObj);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeDelete
        (JNIEnv *env, jobject thisObject, jlong executorContextPointer) {
    WasmEdge_ExecutorContext *exeCxt = (WasmEdge_ExecutorContext *)executorContextPointer;
    WasmEdge_ExecutorDelete(exeCxt);
}
