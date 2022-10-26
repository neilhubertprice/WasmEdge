//
// Created by Kenvi Zhu on 2022-03-14.
//

#include "wasmedge/wasmedge.h"
#include "jni.h"
#include "common.h"
#include "FunctionTypeInstance.h"
#include "MemoryInstanceContext.h"
#include "GlobalInstanceContext.h"
#include "TableInstanceContext.h"

JNIEXPORT jlong JNICALL Java_org_wasmedge_ImportObjectContext_nativeInit
        (JNIEnv *env, jobject thisObject, jstring moduleName) {
    WasmEdge_ImportObjectContext *impCxt = WasmEdge_ImportObjectCreate(JStringToWasmString(env, moduleName));
    return (jlong)impCxt;
}

JNIEXPORT void JNICALL Java_org_wasmedge_ImportObjectContext_nativeInitWASI
        (JNIEnv *env, jobject thisObject, jlong importObjectPointer, jobjectArray jArgs, jobjectArray jEnvs,
        jobjectArray jPreopens) {
    WasmEdge_ImportObjectContext *impCxt = (WasmEdge_ImportObjectContext *)importObjectPointer;

    const char** args = JStringArrayToPtrArray(env, jArgs);
    const char** envs = JStringArrayToPtrArray(env, jEnvs);
    const char** preopens = JStringArrayToPtrArray(env, jPreopens);

    WasmEdge_ImportObjectInitWASI(impCxt, args, (*env)->GetArrayLength(env, jArgs),
                                  envs, (*env)->GetArrayLength(env, jEnvs),
                                  preopens, (*env)->GetArrayLength(env, jPreopens));
    ReleasePtrArray(env, jArgs, args);
    ReleasePtrArray(env, jEnvs, envs);
    ReleasePtrArray(env, jPreopens, preopens);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_ImportObjectContext_nativeGetWASIExitCode
        (JNIEnv *env, jobject thisObject, jlong importObjectPointer) {
    WasmEdge_ImportObjectContext *impCxt = (WasmEdge_ImportObjectContext *)importObjectPointer;
    return WasmEdge_ImportObjectWASIGetExitCode(impCxt);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ImportObjectContext_nativeCreateWasmEdgeProcess
        (JNIEnv *env, jclass thisClass, jobjectArray jAllowedCmds, jboolean jAllowAll) {
    const char **allowedCmds = JStringArrayToPtrArray(env, jAllowedCmds);

    WasmEdge_ImportObjectContext *impCxt = WasmEdge_ImportObjectCreateWasmEdgeProcess(allowedCmds, (*env)->GetArrayLength(env, jAllowedCmds), jAllowAll);

    ReleasePtrArray(env, jAllowedCmds, allowedCmds);

    return (jlong)impCxt;
}

JNIEXPORT void JNICALL Java_org_wasmedge_ImportObjectContext_nativeInitWasmEdgeProcess
        (JNIEnv *env, jobject thisObject, jlong importObjectPointer, jobjectArray jAllowedCmds, jboolean jAllowAll) {
    WasmEdge_ImportObjectContext *impCxt = (WasmEdge_ImportObjectContext *)importObjectPointer;

    const char** allowedCmds = JStringArrayToPtrArray(env, jAllowedCmds);
    WasmEdge_ImportObjectInitWasmEdgeProcess(impCxt, allowedCmds, (*env)->GetArrayLength(env, jAllowedCmds), jAllowAll);

    ReleasePtrArray(env, jAllowedCmds, allowedCmds);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ImportObjectContext_nativeAddFunction
        (JNIEnv *env, jobject thisObject, jlong importObjectPointer, jstring jFuncName, jlong funcPointer) {
    WasmEdge_ImportObjectContext *impObjCxt = (WasmEdge_ImportObjectContext *)importObjectPointer;
    WasmEdge_FunctionInstanceContext *funcInst = (WasmEdge_FunctionInstanceContext *)funcPointer;

    WasmEdge_ImportObjectAddFunction(impObjCxt, JStringToWasmString(env, jFuncName), funcInst);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ImportObjectContext_nativeAddTable
        (JNIEnv *env, jobject thisObject, jlong importObjectPointer, jstring jTabName, jlong tableInstancePointer) {
    WasmEdge_ImportObjectContext *impObjCxt = (WasmEdge_ImportObjectContext *)importObjectPointer;
    WasmEdge_TableInstanceContext *tabIns = (WasmEdge_TableInstanceContext *)tableInstancePointer;
    WasmEdge_ImportObjectAddTable(impObjCxt, JStringToWasmString(env, jTabName), tabIns);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ImportObjectContext_nativeAddMemory
        (JNIEnv *env, jobject thisObject, jlong importObjectPointer, jstring jMemName, jlong memoryInstancePointer) {
    WasmEdge_ImportObjectContext *impObjCxt = (WasmEdge_ImportObjectContext *)importObjectPointer;
    WasmEdge_MemoryInstanceContext *memCxt = (WasmEdge_MemoryInstanceContext *)memoryInstancePointer;

    WasmEdge_ImportObjectAddMemory(impObjCxt, JStringToWasmString(env, jMemName), memCxt);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ImportObjectContext_nativeAddGlobal
        (JNIEnv *env, jobject thisObject, jlong importObjectPointer, jstring jGlobalName, jlong globalInstancePointer) {
    WasmEdge_ImportObjectContext *impObjCxt = (WasmEdge_ImportObjectContext *)importObjectPointer;
    WasmEdge_GlobalInstanceContext *globalInstance = (WasmEdge_GlobalInstanceContext *)globalInstancePointer;
    WasmEdge_ImportObjectAddGlobal(impObjCxt, JStringToWasmString(env, jGlobalName), globalInstance);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ImportObjectContext_nativeDelete
        (JNIEnv *env, jobject thisObject, jlong importObjectPointer) {
    WasmEdge_ImportObjectContext *impObjCxt = (WasmEdge_ImportObjectContext *)importObjectPointer;
    WasmEdge_ImportObjectDelete(impObjCxt);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ImportObjectContext_nativeCreateWASI
        (JNIEnv *env , jclass thisClass, jobjectArray jArgs, jobjectArray jEnvs, jobjectArray jPreopens) {
    const char** args = JStringArrayToPtrArray(env, jArgs);
    const char** envs = JStringArrayToPtrArray(env, jEnvs);
    const char** preopens = JStringArrayToPtrArray(env, jPreopens);

    WasmEdge_ImportObjectContext *importObjectContext = WasmEdge_ImportObjectCreateWASI(args, (*env)->GetArrayLength(env, jArgs),
                                    envs, (*env)->GetArrayLength(env,jEnvs),
                                    preopens, (*env)->GetArrayLength(env,jPreopens));

    ReleasePtrArray(env, jArgs, args);
    ReleasePtrArray(env, jEnvs, envs);
    ReleasePtrArray(env, jPreopens, preopens);

    return (jlong)importObjectContext;
}

