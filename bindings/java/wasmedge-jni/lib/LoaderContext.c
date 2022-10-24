//
// Created by Kenvi Zhu on 2021-12-19.
//

#include "wasmedge/wasmedge.h"
#include "common.h"
#include "ConfigureContext.h"
#include "AstModuleContext.h"

JNIEXPORT jlong JNICALL Java_org_wasmedge_LoaderContext_nativeParseFromFile
        (JNIEnv * env, jobject thisObject, jlong loaderContextPointer, jstring jInputPath) {
    WasmEdge_LoaderContext *loader = (WasmEdge_LoaderContext *)loaderContextPointer;

    WasmEdge_ASTModuleContext *mod = NULL;

    const char *inputPath = (*env)->GetStringUTFChars(env, jInputPath, NULL);
    WasmEdge_Result result = WasmEdge_LoaderParseFromFile(loader, &mod, inputPath);
    (*env)->ReleaseStringUTFChars(env, jInputPath, inputPath);

    handleWasmEdgeResult(env, &result);

    if((*env)->ExceptionOccurred(env)) {
        return 0;
    }

    return (jlong)mod;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_LoaderContext_nativeParseFromBuffer
        (JNIEnv * env, jobject thisObject, jlong loaderContextPointer, jbyteArray jBuf, jint jSize) {
    WasmEdge_LoaderContext *loader = (WasmEdge_LoaderContext *)loaderContextPointer;

    WasmEdge_ASTModuleContext *mod = NULL;

    jbyte *data = (*env)->GetByteArrayElements(env, jBuf, NULL);

    WasmEdge_LoaderParseFromBuffer(loader, &mod, (uint8_t*)data, jSize);

    (*env)->ReleaseByteArrayElements(env, jBuf, data, 0);

    return (jlong)mod;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_LoaderContext_nativeInit
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
   WasmEdge_ConfigureContext *configureContext = (WasmEdge_ConfigureContext *)configContextPointer;
   WasmEdge_LoaderContext* loaderContext = WasmEdge_LoaderCreate(configureContext);
   return (jlong)loaderContext;
}


JNIEXPORT void JNICALL Java_org_wasmedge_LoaderContext_nativeDelete
        (JNIEnv * env, jobject thisObject, jlong loaderContextPointer) {
    WasmEdge_LoaderContext *loader = (WasmEdge_LoaderContext *)loaderContextPointer;
    WasmEdge_LoaderDelete(loader);
}
