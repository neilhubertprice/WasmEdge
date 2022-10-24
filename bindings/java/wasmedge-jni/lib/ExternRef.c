//
// Created by Kenvi Zhu on 2022-01-16.
//
#include <stdlib.h>
#include "common.h"
#include <string.h>

// TODO: this is currently incorrect as it uses the address of a WasmEdge_Value struct on the local stack frame
// (This behaviour is carried over from pre-existing code & all that changed here was the mechanism for passing the long around)
// TODO: this needs reworking to use long references that don't need freeing (instead of strings)
JNIEXPORT jlong JNICALL Java_org_wasmedge_WasmEdgeExternRef_nativeInit
        (JNIEnv * env, jobject thisObject, jobject jVal) {
    jint len = (*env)->GetStringUTFLength(env, jVal);

    // Where does this get free'd?
    char *ptr = (char*)malloc(sizeof(char ) * len);

    const char* val = (*env)->GetStringUTFChars(env, jVal, NULL);
    memcpy(ptr, val, len);
    (*env)->ReleaseStringUTFChars(env, jVal, val);

    WasmEdge_Value ref = WasmEdge_ValueGenExternRef(ptr);

    return (jlong)&ref;
}

