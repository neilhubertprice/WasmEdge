//
// Created by Kenvi Zhu on 2022-03-03.
//

#include "ExportTypeContext.h"
#include "jni.h"
#include "wasmedge/wasmedge.h"
#include "AstModuleContext.h"
#include "FunctionTypeContext.h"
#include "GlobalTypeContext.h"
#include "MemoryTypeContext.h"
#include "TableTypeContext.h"
#include "common.h"


JNIEXPORT jstring JNICALL Java_org_wasmedge_ExportTypeContext_getExternalName
        (JNIEnv *env, jobject thisObject, jlong exportTypePointer) {
    WasmEdge_ExportTypeContext *expType = (WasmEdge_ExportTypeContext *)exportTypePointer;

    WasmEdge_String wName = WasmEdge_ExportTypeGetExternalName(expType);

    return WasmEdgeStringToJString(env, wName);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_ExportTypeContext_nativeGetExternalType
        (JNIEnv * env, jobject thisObject, jlong exportTypePointer) {
   WasmEdge_ExportTypeContext *expType = (WasmEdge_ExportTypeContext *)exportTypePointer;

    enum WasmEdge_ExternalType type = WasmEdge_ExportTypeGetExternalType(expType);
    return type;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ExportTypeContext_nativeGetFunctionType
        (JNIEnv *env, jobject thisObject, jlong exportTypePointer, jlong astmContextPointer) {
    WasmEdge_ExportTypeContext *expType = (WasmEdge_ExportTypeContext *)exportTypePointer;
    WasmEdge_ASTModuleContext *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;
    const WasmEdge_FunctionTypeContext *functionTypeContext =  WasmEdge_ExportTypeGetFunctionType(astCxt, expType);
    return (jlong)functionTypeContext;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ExportTypeContext_nativeGetTableType
        (JNIEnv *env, jobject thisObject, jlong exportTypePointer, jlong astmContextPointer) {
    WasmEdge_ExportTypeContext *expType = (WasmEdge_ExportTypeContext *)exportTypePointer;
    WasmEdge_ASTModuleContext *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;
    const WasmEdge_TableTypeContext *tableCxt = WasmEdge_ExportTypeGetTableType(astCxt, expType);

    return (jlong)tableCxt;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ExportTypeContext_nativeGetMemoryType
        (JNIEnv *env, jobject thisObject, jlong exportTypePointer, jlong astmContextPointer) {
    WasmEdge_ExportTypeContext *expType = (WasmEdge_ExportTypeContext *)exportTypePointer;
    WasmEdge_ASTModuleContext *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

    const WasmEdge_MemoryTypeContext *memCxt = WasmEdge_ExportTypeGetMemoryType(astCxt, expType);
    return (jlong)memCxt;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ExportTypeContext_nativeGetGlobalType
        (JNIEnv *env, jobject thisObject, jlong exportTypePointer, jlong astmContextPointer) {
    WasmEdge_ExportTypeContext *expType = (WasmEdge_ExportTypeContext *)exportTypePointer;
    WasmEdge_ASTModuleContext *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

    const WasmEdge_GlobalTypeContext *globalCxt = WasmEdge_ExportTypeGetGlobalType(astCxt, expType);

    return (jlong)globalCxt;
}
