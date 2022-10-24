//
// Created by Kenvi Zhu on 2022-03-03.
//

#include "ImportTypeContext.h"
#include "jni.h"
#include "wasmedge/wasmedge.h"
#include "AstModuleContext.h"
#include "FunctionTypeContext.h"
#include "GlobalTypeContext.h"
#include "MemoryTypeContext.h"
#include "TableTypeContext.h"
#include "common.h"


JNIEXPORT jstring JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetModuleName
        (JNIEnv *env, jobject thisObject, jlong importTypePointer) {
    WasmEdge_ImportTypeContext *impType = (WasmEdge_ImportTypeContext *)importTypePointer;

    WasmEdge_String wModName = WasmEdge_ImportTypeGetModuleName(impType);
    return WasmEdgeStringToJString(env, wModName);
}

JNIEXPORT jstring JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetExternalName
        (JNIEnv *env, jobject thisObject, jlong importTypePointer) {
    WasmEdge_ImportTypeContext *impType = (WasmEdge_ImportTypeContext *)importTypePointer;

    WasmEdge_String wName = WasmEdge_ImportTypeGetExternalName(impType);

    return WasmEdgeStringToJString(env, wName);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetExternalType
        (JNIEnv * env, jobject thisObject, jlong importTypePointer) {
   WasmEdge_ImportTypeContext *impType = (WasmEdge_ImportTypeContext *)importTypePointer;

    enum WasmEdge_ExternalType type = WasmEdge_ImportTypeGetExternalType(impType);
    return type;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetFunctionType
        (JNIEnv *env, jobject thisObject, jlong importTypePointer, jlong astmContextPointer) {
    WasmEdge_ImportTypeContext *impType = (WasmEdge_ImportTypeContext *)importTypePointer;
    WasmEdge_ASTModuleContext *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;
    const WasmEdge_FunctionTypeContext *functionTypeContext = WasmEdge_ImportTypeGetFunctionType(astCxt, impType);
    return (jlong)functionTypeContext;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetTableType
        (JNIEnv *env, jobject thisObject, jlong importTypePointer, jlong astmContextPointer) {
    WasmEdge_ImportTypeContext *impType = (WasmEdge_ImportTypeContext *)importTypePointer;
    WasmEdge_ASTModuleContext *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;
    const WasmEdge_TableTypeContext *tableCxt = WasmEdge_ImportTypeGetTableType(astCxt, impType);

    return createJTableTypeContext(env, tableCxt);
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetMemoryType
        (JNIEnv *env, jobject thisObject, jlong importTypePointer, jlong astmContextPointer) {
    WasmEdge_ImportTypeContext *impType = (WasmEdge_ImportTypeContext *)importTypePointer;
    WasmEdge_ASTModuleContext *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

    const WasmEdge_MemoryTypeContext *memCxt = WasmEdge_ImportTypeGetMemoryType(astCxt, impType);
    return createJMemoryTypeContext(env, memCxt);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetGlobalType
        (JNIEnv *env, jobject thisObject, jlong importTypePointer, jlong astmContextPointer) {
    WasmEdge_ImportTypeContext *impType = (WasmEdge_ImportTypeContext *)importTypePointer;
    WasmEdge_ASTModuleContext *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

    const WasmEdge_GlobalTypeContext *globalCxt = WasmEdge_ImportTypeGetGlobalType(astCxt, impType);

    return (jlong)globalCxt;
}
