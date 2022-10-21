//
// Created by Kenvi Zhu on 2021-11-19.
//

#include "wasmedge/wasmedge.h"
#include "common.h"
#include "../jni/org_wasmedge_VMContext.h"
#include "StoreContext.h"
#include "ConfigureContext.h"

JNIEXPORT void JNICALL Java_org_wasmedge_VMContext_initNative
        (JNIEnv * env, jobject jVmContext, jlong configContextPointer, jobject jStoreContext) {
    WasmEdge_ConfigureContext *ConfigureContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_StoreContext * StoreContext = getStoreContext(env, jStoreContext);

    WasmEdge_VMContext* VMContext = WasmEdge_VMCreate(ConfigureContext, StoreContext);

    setPointer(env, jVmContext, (jlong)VMContext);
}