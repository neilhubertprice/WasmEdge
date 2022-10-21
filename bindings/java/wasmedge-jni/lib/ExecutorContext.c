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

WasmEdge_ExecutorContext *getExecutorContext(JNIEnv * env, jobject jExeCtx) {
    if(jExeCtx == NULL) {
        return NULL;
    }

    return (WasmEdge_ExecutorContext*)getPointer(env, jExeCtx);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeInit
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jobject jStatCxt) {
    WasmEdge_ConfigureContext *confCxt = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_StatisticsContext * statCxt = getStatisticsContext(env, jStatCxt);

    WasmEdge_ExecutorContext * exeCxt = WasmEdge_ExecutorCreate(confCxt, statCxt);
    setPointer(env, thisObject, (long)exeCxt);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeInstantiate
        (JNIEnv * env, jobject thisObject, jlong storeContextPointer, jobject jAstModCxt) {
    WasmEdge_ExecutorContext * exeCxt = getExecutorContext(env, thisObject);
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_ASTModuleContext * astModCxt = getASTModuleContext(env, jAstModCxt);

    WasmEdge_ExecutorInstantiate(exeCxt, storeCxt, astModCxt);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeInvoke
        (JNIEnv * env, jobject thisObject, jlong storeContextPointer, jstring jFuncName, jobject jParams, jobject jReturns) {
    WasmEdge_ExecutorContext *exeCxt = getExecutorContext(env, thisObject);
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    jsize paramLen = GetListSize(env, jParams);

    /* The parameters and returns arrays. */
    WasmEdge_Value *wasm_params = calloc(paramLen, sizeof(WasmEdge_Value));
    for (int i = 0; i < paramLen; i++) {
        wasm_params[i] = JavaValueToWasmEdgeValue(env, GetListElement(env, jParams, i));
    }

    uint32_t returnLen = GetReturnLen(WasmEdge_StoreFindFunction(storeCxt, wFuncName));
    WasmEdge_Value *returns = malloc(sizeof(WasmEdge_Value) * returnLen);

    WasmEdge_Result result = WasmEdge_ExecutorInvoke(exeCxt, storeCxt, wFuncName, wasm_params, paramLen, returns, returnLen);

    handleWasmEdgeResult(env, & result);

    if (WasmEdge_ResultOK(result)) {
        for (int i = 0; i < returnLen; ++i) {
            AddElementToJavaList(env, jReturns, WasmEdgeValueToJavaValue(env, returns[i]));
        }
    }

    //release resource
    free(wasm_params);
    free(returns);
    WasmEdge_StringDelete(wFuncName);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeInvokeRegistered
        (JNIEnv *env, jobject thisObject, jlong storeContextPointer, jstring jModName, jstring jFuncName, jobject jParams, jobject jReturns) {
    WasmEdge_ExecutorContext * exeCxt = getExecutorContext(env, thisObject);
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    jsize paramLen = GetListSize(env, jParams);

    /* The parameters and returns arrays. */
    WasmEdge_Value *wasm_params = calloc(paramLen, sizeof(WasmEdge_Value));
    for (int i = 0; i < paramLen; i++) {
        jobject val_object = GetListElement(env, jParams, i);
        wasm_params[i] = JavaValueToWasmEdgeValue(env, val_object);
    }

    jsize returnLen = GetListSize(env, jReturns);
    WasmEdge_Value *returns = malloc(sizeof(WasmEdge_Value) * returnLen);

    WasmEdge_Result result = WasmEdge_ExecutorInvoke(exeCxt, storeCxt, wFuncName, wasm_params, paramLen, returns, returnLen);

    handleWasmEdgeResult(env, & result);

    if (WasmEdge_ResultOK(result)) {
        for (int i = 0; i < returnLen; ++i) {
            AddElementToJavaList(env, jReturns, WasmEdgeValueToJavaValue(env, returns[i]));
        }
    }

    //release resource
    free(wasm_params);
    free(returns);
    WasmEdge_StringDelete(wFuncName);
    WasmEdge_StringDelete(wModName);

}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeRegisterModule
        (JNIEnv * env, jobject thisObject, jlong storeContextPointer, jobject jAstModCxt, jstring jModName) {
    WasmEdge_ExecutorContext *exeCxt = getExecutorContext(env, thisObject);
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_ASTModuleContext * astModCxt = getASTModuleContext(env, jAstModCxt);

    WasmEdge_String wModName = JStringToWasmString(env, jModName);

    WasmEdge_Result result = WasmEdge_ExecutorRegisterModule(exeCxt, storeCxt, astModCxt, wModName);

    handleWasmEdgeResult(env, &result);

    WasmEdge_StringDelete(wModName);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_nativeRegisterImport
        (JNIEnv *env, jobject thisObject, jlong storeContextPointer, jobject jImpObj) {
    WasmEdge_ExecutorContext *exeCxt = getExecutorContext(env, thisObject);
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_ImportObjectContext *impObj = getImportObjectContext(env, jImpObj);

    WasmEdge_ExecutorRegisterImport(exeCxt, storeCxt, impObj);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ExecutorContext_delete
        (JNIEnv * env, jobject thisObject) {
    WasmEdge_ExecutorContext *exeCxt = getExecutorContext(env, thisObject);
    WasmEdge_ExecutorDelete(exeCxt);
}
