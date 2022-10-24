//
// Created by Kenvi Zhu on 2021-11-19.
//

#include "wasmedge/wasmedge.h"
#include "common.h"
#include "StoreContext.h"
#include "ConfigureContext.h"

JNIEXPORT jlong JNICALL Java_org_wasmedge_VMContext_initNative
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jlong storeContextPointer) {
    WasmEdge_ConfigureContext *ConfigureContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_StoreContext *StoreContext = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_VMContext* VMContext = WasmEdge_VMCreate(ConfigureContext, StoreContext);

    return (jlong)VMContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_VMContext_nativeCleanup
        (JNIEnv *env, jobject thisObject, jlong vmContextPointer) {
    WasmEdge_VMContext *vmContext = (WasmEdge_VMContext *)vmContextPointer;
    WasmEdge_VMCleanup(vmContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_VMContext_nativeDelete
        (JNIEnv *env, jobject thisObject, jlong vmContextPointer) {
    WasmEdge_VMContext *vmContext = (WasmEdge_VMContext *)vmContextPointer;
    WasmEdge_VMDelete(vmContext);
}

