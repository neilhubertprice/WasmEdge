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

WasmEdge_ImportTypeContext *getImportTypeContext(JNIEnv * env, jobject jExpType) {
    if(jExpType == NULL) {
        return NULL;
    }

    return (WasmEdge_ImportTypeContext *)getPointer(env, jExpType);
}

JNIEXPORT jstring JNICALL Java_org_wasmedge_ImportTypeContext_getModuleName
        (JNIEnv *env, jobject thisObject) {

    WasmEdge_ImportTypeContext * impType = getImportTypeContext(env, thisObject);

    WasmEdge_String wModName = WasmEdge_ImportTypeGetModuleName(impType);
    return WasmEdgeStringToJString(env, wModName);
}

JNIEXPORT jstring JNICALL Java_org_wasmedge_ImportTypeContext_getExternalName
        (JNIEnv *env, jobject thisObject) {
    WasmEdge_ImportTypeContext *expType = getImportTypeContext(env, thisObject);

    WasmEdge_String wName = WasmEdge_ImportTypeGetExternalName(expType);

    return WasmEdgeStringToJString(env, wName);

}

JNIEXPORT jint JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetExternalType
        (JNIEnv * env, jobject thisObject) {
   WasmEdge_ImportTypeContext *expType = getImportTypeContext(env, thisObject);

    enum WasmEdge_ExternalType type = WasmEdge_ImportTypeGetExternalType(expType);
    return type;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetFunctionType
        (JNIEnv *env, jobject thisObject, jlong astmContextPointer) {
    WasmEdge_ImportTypeContext  *expType = getImportTypeContext(env, thisObject);
    WasmEdge_ASTModuleContext  *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;
    const WasmEdge_FunctionTypeContext *functionTypeContext = WasmEdge_ImportTypeGetFunctionType(astCxt, expType);
    return (jlong)functionTypeContext;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetTableType
        (JNIEnv *env, jobject thisObject, jlong astmContextPointer) {
    WasmEdge_ImportTypeContext  *expType = getImportTypeContext(env, thisObject);
    WasmEdge_ASTModuleContext  *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;
    const WasmEdge_TableTypeContext *tableCxt = WasmEdge_ImportTypeGetTableType(astCxt, expType);

    return createJTableTypeContext(env, tableCxt);

}

JNIEXPORT jobject JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetMemoryType
        (JNIEnv *env, jobject thisObject, jlong astmContextPointer) {
    WasmEdge_ImportTypeContext  *expType = getImportTypeContext(env, thisObject);
    WasmEdge_ASTModuleContext  *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

    const WasmEdge_MemoryTypeContext *memCxt = WasmEdge_ImportTypeGetMemoryType(astCxt, expType);
    return createJMemoryTypeContext(env, memCxt);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ImportTypeContext_nativeGetGlobalType
        (JNIEnv *env, jobject thisObject, jlong astmContextPointer) {
    WasmEdge_ImportTypeContext  *impType = getImportTypeContext(env, thisObject);
    WasmEdge_ASTModuleContext  *astCxt = (WasmEdge_ASTModuleContext *)astmContextPointer;

    const WasmEdge_GlobalTypeContext *globalCxt = WasmEdge_ImportTypeGetGlobalType(astCxt, impType);

    return (jlong)globalCxt;
}

jobject createImportTypeContext(JNIEnv * env, const WasmEdge_ImportTypeContext * cxt, jobject jAstMod) {

    jclass cls = findJavaClass(env, "org/wasmedge/ImportTypeContext");
    jmethodID constructor = findJavaMethod(env, cls, "<init>", "(JLorg/wasmedge/ASTModuleContext;)V");
    jobject obj = (*env)->NewObject(env, cls, constructor, (long)cxt, jAstMod);
    return obj;
}

