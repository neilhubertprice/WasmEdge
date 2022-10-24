//
// Created by Kenvi Zhu on 2022-01-10.
//

#include "jni.h"
#include "wasmedge/wasmedge.h"
#include "common.h"
#include "AstModuleContext.h"
#include "ConfigureContext.h"


JNIEXPORT void JNICALL Java_org_wasmedge_ValidatorContext_nativeValidate
        (JNIEnv * env, jobject thisObject, jlong validatorContextPointer, jlong astmContextPointer) {
   WasmEdge_ValidatorContext *validatorContext = (WasmEdge_ValidatorContext *)validatorContextPointer;
   WasmEdge_ASTModuleContext *astModCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

   WasmEdge_Result result = WasmEdge_ValidatorValidate(validatorContext, astModCxt);
   handleWasmEdgeResult(env, &result);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ValidatorContext_nativeInit
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configureContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ValidatorContext *validatorContext = WasmEdge_ValidatorCreate(configureContext);

    return (jlong)validatorContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_ValidatorContext_nativeDelete
        (JNIEnv *env, jobject thisObject, jlong validatorContextPointer) {
    WasmEdge_ValidatorContext *validatorContext = (WasmEdge_ValidatorContext *)validatorContextPointer;
    WasmEdge_ValidatorDelete(validatorContext);
}
