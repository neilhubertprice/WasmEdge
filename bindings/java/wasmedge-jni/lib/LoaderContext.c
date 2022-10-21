//
// Created by Kenvi Zhu on 2021-12-19.
//

#include "wasmedge/wasmedge.h"
#include "common.h"
#include "ConfigureContext.h"
#include "AstModuleContext.h"

WasmEdge_LoaderContext * getLoader(JNIEnv *env, jobject jLoader) {
    return (WasmEdge_LoaderContext*)getPointer(env, jLoader);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_LoaderContext_nativeParseFromFile
        (JNIEnv * env, jobject thisObject, jstring jInputPath) {
    WasmEdge_LoaderContext *loader = getLoader(env, thisObject);

    const char *inputPath = (*env)->GetStringUTFChars(env, jInputPath, NULL);

    WasmEdge_ASTModuleContext *mod = NULL;

    WasmEdge_Result result = WasmEdge_LoaderParseFromFile(loader, &mod, inputPath);
    (*env)->ReleaseStringUTFChars(env, jInputPath, inputPath);
    handleWasmEdgeResult(env, &result);

    if((*env)->ExceptionOccurred(env)) {
        return NULL;
    }

    return (jlong)mod;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_LoaderContext_nativeParseFromBuffer
        (JNIEnv * env, jobject thisObject, jbyteArray jBuf, jint jSize) {
    WasmEdge_LoaderContext *loader = getLoader(env, thisObject);

    WasmEdge_ASTModuleContext *mod = NULL;

    jbyte *data = (*env)->GetByteArrayElements(env, jBuf, NULL);

    WasmEdge_LoaderParseFromBuffer(loader, &mod, (uint8_t*)data, jSize);

    (*env)->ReleaseByteArrayElements(env, jBuf, data, 0);

    return (jlong)mod;
}

JNIEXPORT void JNICALL Java_org_wasmedge_LoaderContext_nativeInit
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
   WasmEdge_ConfigureContext *configureContext = (WasmEdge_ConfigureContext *)configContextPointer;
   WasmEdge_LoaderContext* loaderContext = WasmEdge_LoaderCreate(configureContext);
   setPointer(env, thisObject, (long)loaderContext);
}


JNIEXPORT void JNICALL Java_org_wasmedge_LoaderContext_delete
        (JNIEnv * env, jobject thisObject) {

    WasmEdge_LoaderContext *loader = getLoader(env, thisObject);
    WasmEdge_LoaderDelete(loader);
}
