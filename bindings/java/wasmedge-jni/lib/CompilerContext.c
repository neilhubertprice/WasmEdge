//
// Created by Kenvi Zhu on 2021-12-16.
//
#include "wasmedge/wasmedge.h"
#include "ConfigureContext.h"
#include "common.h"

JNIEXPORT jlong JNICALL Java_org_wasmedge_CompilerContext_nativeInit
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configureContext = (WasmEdge_ConfigureContext *)configContextPointer;

    WasmEdge_CompilerContext* compilerContext =  WasmEdge_CompilerCreate(configureContext);

    return (jlong)compilerContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_CompilerContext_nativeCompile
        (JNIEnv * env, jobject thisObject, jlong compilerContextPointer, jstring jInputPath, jstring jOutputPath) {
    WasmEdge_CompilerContext *compilerContext = (WasmEdge_CompilerContext *)compilerContextPointer;

    const char* inputPath = (*env)->GetStringUTFChars(env, jInputPath, NULL);
    const char* outputPath = (*env)->GetStringUTFChars(env, jOutputPath, NULL);

    WasmEdge_Result result = WasmEdge_CompilerCompile(compilerContext, inputPath, outputPath);

    (*env)->ReleaseStringUTFChars(env, jInputPath, inputPath);
    (*env)->ReleaseStringUTFChars(env, jOutputPath, outputPath);

    handleWasmEdgeResult(env, &result);
}

JNIEXPORT void JNICALL Java_org_wasmedge_CompilerContext_nativeDelete
        (JNIEnv * env, jobject thisObject, jlong compilerContextPointer) {
    WasmEdge_CompilerContext *compilerContext = (WasmEdge_CompilerContext *)compilerContextPointer;
    WasmEdge_CompilerDelete(compilerContext);
}

