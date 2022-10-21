//
// Created by Kenvi Zhu on 2021-11-17.
//
#include <stdlib.h>
#include "jni.h"
#include "wasmedge/wasmedge.h"
#include "common.h"
#include "FunctionTypeInstance.h"
#include "GlobalInstanceContext.h"
#include "TableInstanceContext.h"
#include "MemoryInstanceContext.h"

JNIEXPORT jlong JNICALL Java_org_wasmedge_StoreContext_nativeInit
        (JNIEnv *env, jobject thisObj) {
    WasmEdge_StoreContext *StoreContext = WasmEdge_StoreCreate();
    return (jlong)StoreContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_StoreContext_nativeDelete
        (JNIEnv * env, jobject thisObj, jlong storeContextPointer) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_StoreDelete(storeCxt);
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListFunction
        (JNIEnv *env , jobject thisObject, jlong storeContextPointer) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    uint32_t funcLen = WasmEdge_StoreListFunctionLength(storeCxt);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * funcLen);
    uint32_t realFuncNum = WasmEdge_StoreListFunction(storeCxt, nameList, funcLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, realFuncNum);

    free(nameList);

    return jNameList;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_StoreContext_nativeFindFunction
        (JNIEnv *env, jobject thisObject, jlong storeContextPointer, jstring jFuncName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    WasmEdge_FunctionInstanceContext *funcInstance = WasmEdge_StoreFindFunction(storeCxt, wFuncName);

    WasmEdge_StringDelete(wFuncName);

    return (jlong)funcInstance;
}


JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListFunctionRegistered
        (JNIEnv * env, jobject thisObject, jlong storeContextPointer, jstring jModName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

	WasmEdge_String wModName = JStringToWasmString(env, jModName);

    uint32_t funcLen = WasmEdge_StoreListFunctionRegisteredLength(storeCxt, wModName);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * funcLen);
    uint32_t realFuncNum = WasmEdge_StoreListFunctionRegistered(storeCxt, wModName, nameList, funcLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, realFuncNum);

    free(nameList);
    WasmEdge_StringDelete(wModName);

    return jNameList;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_StoreContext_nativeFindFunctionRegistered
        (JNIEnv *env, jobject thisObject, jlong storeContextPointer, jstring jModName, jstring jFuncName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    const WasmEdge_FunctionInstanceContext *funcInst = WasmEdge_StoreFindFunctionRegistered(storeCxt, wModName, wFuncName);

    WasmEdge_StringDelete(wFuncName);
    WasmEdge_StringDelete(wModName);

    return (long)funcInst;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListTable
        (JNIEnv *env , jobject thisObject, jlong storeContextPointer) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    uint32_t tabLen = WasmEdge_StoreListTableLength(storeCxt);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * tabLen);
    uint32_t realTabNum = WasmEdge_StoreListTable(storeCxt, nameList, tabLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, realTabNum);

    free(nameList);

    return jNameList;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeFindTable
        (JNIEnv *env , jobject thisObject, jlong storeContextPointer, jstring jTabName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_String wTabName = JStringToWasmString(env, jTabName);

    WasmEdge_TableInstanceContext * tabInst = WasmEdge_StoreFindTable(storeCxt, wTabName);
    jobject jTabInst = createJTableInstanceContext(env, tabInst);

    WasmEdge_StringDelete(wTabName);

    return jTabInst;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeFindTableRegistered
        (JNIEnv *env, jobject thisObject, jlong storeContextPointer, jstring jModName, jstring jTabName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    WasmEdge_String wTabName = JStringToWasmString(env, jTabName);

    WasmEdge_TableInstanceContext * tabInst = WasmEdge_StoreFindTableRegistered(storeCxt, wModName, wTabName);
    jobject jTabInst = createJTableInstanceContext(env, tabInst);

    WasmEdge_StringDelete(wTabName);
    WasmEdge_StringDelete(wModName);

    return jTabInst;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListTableRegistered
        (JNIEnv * env, jobject thisObject, jlong storeContextPointer, jstring jModName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wModName = JStringToWasmString(env, jModName);

    uint32_t tabLen = WasmEdge_StoreListTableRegisteredLength(storeCxt, wModName);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * tabLen);
    uint32_t realTabNum = WasmEdge_StoreListTableRegistered(storeCxt, wModName, nameList, tabLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, realTabNum);

    free(nameList);
    WasmEdge_StringDelete(wModName);

    return jNameList;
};

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListMemory
        (JNIEnv *env , jobject thisObject, jlong storeContextPointer) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    uint32_t memLen = WasmEdge_StoreListMemoryLength(storeCxt);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * memLen);
    uint32_t realMemNum = WasmEdge_StoreListMemory(storeCxt, nameList, memLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, realMemNum);

    free(nameList);

    return jNameList;
};

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListMemoryRegistered
        (JNIEnv * env, jobject thisObject, jlong storeContextPointer, jstring jModName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wModName = JStringToWasmString(env, jModName);

    uint32_t memLen = WasmEdge_StoreListMemoryRegisteredLength(storeCxt, wModName);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * memLen);
    uint32_t realModNum = WasmEdge_StoreListMemoryRegistered(storeCxt, wModName, nameList, memLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, realModNum);

    free(nameList);
    WasmEdge_StringDelete(wModName);

    return jNameList;
};

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeFindMemory
        (JNIEnv *env , jobject thisObject, jlong storeContextPointer, jstring jMemName) {
    WasmEdge_StoreContext* storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wMemName = JStringToWasmString(env, jMemName);

    WasmEdge_MemoryInstanceContext * memInst = WasmEdge_StoreFindMemory(storeCxt, wMemName);
    jobject jMemInst = createJMemoryInstanceContext(env, memInst);

    WasmEdge_StringDelete(wMemName);

    return jMemInst;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeFindMemoryRegistered
        (JNIEnv *env, jobject thisObject, jlong storeContextPointer, jstring jModName, jstring jMemName) {
    WasmEdge_StoreContext* storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    WasmEdge_String wMemName = JStringToWasmString(env, jMemName);

    WasmEdge_MemoryInstanceContext * memInst = WasmEdge_StoreFindMemoryRegistered(storeCxt, wModName, wMemName);
    jobject jMemInst = createJMemoryInstanceContext(env, memInst);

    WasmEdge_StringDelete(wMemName);
    WasmEdge_StringDelete(wModName);

    return jMemInst;

}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListGlobal
        (JNIEnv *env , jobject thisObject, jlong storeContextPointer) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    uint32_t globLen = WasmEdge_StoreListGlobalLength(storeCxt);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * globLen);
    uint32_t RealGlobNum = WasmEdge_StoreListGlobal(storeCxt, nameList, globLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, RealGlobNum);

    free(nameList);

    return jNameList;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListGlobalRegistered
        (JNIEnv * env, jobject thisObject, jlong storeContextPointer, jstring jModName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_String wModName = JStringToWasmString(env, jModName);

    uint32_t modLen = WasmEdge_StoreListGlobalRegisteredLength(storeCxt, wModName);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * modLen);
    uint32_t realModNum = WasmEdge_StoreListGlobalRegistered(storeCxt, wModName, nameList, modLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, realModNum);

    free(nameList);
    WasmEdge_StringDelete(wModName);

    return jNameList;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeFindGlobal
        (JNIEnv * env, jobject thisObject, jlong storeContextPointer, jstring jGlobName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_String wGlobName = JStringToWasmString(env, jGlobName);

    WasmEdge_GlobalInstanceContext * globInst = WasmEdge_StoreFindGlobal(storeCxt, wGlobName);
    
    WasmEdge_StringDelete(wGlobName);

    return createJGlobalInstanceContext(env, globInst);
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeFindGlobalRegistered
        (JNIEnv *env, jobject thisObject, jlong storeContextPointer, jstring jModName, jstring jGlobName) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;
    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    WasmEdge_String wGlobName = JStringToWasmString(env, jGlobName);

    WasmEdge_GlobalInstanceContext * globInst = WasmEdge_StoreFindGlobalRegistered(storeCxt, wModName, wGlobName);
    jobject jGlob = createJGlobalInstanceContext(env, globInst);

    WasmEdge_StringDelete(wGlobName);
    WasmEdge_StringDelete(wModName);

    return jGlob;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_StoreContext_nativeListModule
        (JNIEnv *env, jobject thisObject, jlong storeContextPointer) {
    WasmEdge_StoreContext *storeCxt = (WasmEdge_StoreContext *)storeContextPointer;

    uint32_t modLen = WasmEdge_StoreListModuleLength(storeCxt);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * modLen);
    uint32_t realModNum = WasmEdge_StoreListModule(storeCxt, nameList, modLen);

    jobject jNameList = WasmEdgeStringArrayToJavaList(env, nameList, realModNum);

    free(nameList);

    return jNameList;
};

