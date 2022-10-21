//
// Created by Kenvi Zhu on 2021-11-19.
//

#include "common.h"
#include "wasmedge/wasmedge.h"
#include <stdint.h>

JNIEXPORT jlong JNICALL Java_org_wasmedge_ConfigureContext_nativeInit
        (JNIEnv * env, jobject thisObj) {
    WasmEdge_ConfigureContext *ConfigureContext = WasmEdge_ConfigureCreate();
    return (jlong)ConfigureContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeDelete
        (JNIEnv *env, jobject thisObj, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureDelete(configContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeAddProposal
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jint proposal) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureAddProposal(configContext, (enum WasmEdge_Proposal) proposal);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeRemoveProposal
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jint proposal) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureRemoveProposal(configContext, (enum WasmEdge_Proposal) proposal);
}

JNIEXPORT jboolean JNICALL Java_org_wasmedge_ConfigureContext_nativeHasProposal
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jint proposal) {
     WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
   return WasmEdge_ConfigureHasProposal(configContext, (enum WasmEdge_Proposal) proposal);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeAddHostRegistration
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jint hostRegistration) {
     WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
   WasmEdge_ConfigureAddHostRegistration(configContext, (enum WasmEdge_HostRegistration) hostRegistration);
}


JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeRemoveHostRegistration
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jint hostRegistration) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureRemoveHostRegistration(configContext, (enum WasmEdge_HostRegistration) hostRegistration);
}

JNIEXPORT jboolean JNICALL Java_org_wasmedge_ConfigureContext_nativeHasHostRegistration
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jint hostRegistration) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return WasmEdge_ConfigureHasHostRegistration(configContext, (enum WasmEdge_HostRegistration) hostRegistration);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeSetMaxMemoryPage
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jlong maxPage) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureSetMaxMemoryPage(configContext, (uint32_t)maxPage);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_ConfigureContext_nativeGetMaxMemoryPage
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return (jlong)WasmEdge_ConfigureGetMaxMemoryPage(configContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeSetCompilerOptimizationLevel
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jint optimizationLevel) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureCompilerSetOptimizationLevel(configContext,
                                                   (enum WasmEdge_CompilerOptimizationLevel)optimizationLevel);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_ConfigureContext_nativeGetCompilerOptimizationLevel
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return (jint)WasmEdge_ConfigureCompilerGetOptimizationLevel(configContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeSetCompilerOutputFormat
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jint outputFormat) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureCompilerSetOutputFormat(configContext,
                                              (enum WasmEdge_CompilerOutputFormat) outputFormat);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_ConfigureContext_nativeGetCompilerOutputFormat
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return (jint)WasmEdge_ConfigureCompilerGetOutputFormat(configContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeSetCompilerIsDumpIR
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jboolean isDumpIR) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureCompilerSetDumpIR(configContext, isDumpIR);
}

JNIEXPORT jboolean JNICALL Java_org_wasmedge_ConfigureContext_nativeGetCompilerIsDumpIR
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return WasmEdge_ConfigureCompilerIsDumpIR(configContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeSetCompilerIsGenericBinary
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jboolean isGenericBinary) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureCompilerSetGenericBinary(configContext, isGenericBinary);
}

JNIEXPORT jboolean JNICALL Java_org_wasmedge_ConfigureContext_nativeGetCompilerIsGenericBinary
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return WasmEdge_ConfigureCompilerIsGenericBinary(configContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeSetStatisticsSetInstructionCounting
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jboolean instructionCounting) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureStatisticsSetInstructionCounting(configContext, instructionCounting);
}

JNIEXPORT jboolean JNICALL Java_org_wasmedge_ConfigureContext_nativeIsStatisticsSetInstructionCounting
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return WasmEdge_ConfigureStatisticsIsInstructionCounting(configContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeSetStatisticsSetCostMeasuring
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jboolean costMeasuring) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureStatisticsSetCostMeasuring(configContext, costMeasuring);
}

JNIEXPORT jboolean JNICALL Java_org_wasmedge_ConfigureContext_nativeIsStatisticsSetCostMeasuring
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return WasmEdge_ConfigureStatisticsIsCostMeasuring(configContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_ConfigureContext_nativeSetStatisticsSetTimeMeasuring
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jboolean timeMeasuring) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_ConfigureStatisticsSetTimeMeasuring(configContext, timeMeasuring);
}

JNIEXPORT jboolean JNICALL Java_org_wasmedge_ConfigureContext_nativeIsStatisticsSetTimeMeasuring
        (JNIEnv * env, jobject thisObject, jlong configContextPointer) {
    WasmEdge_ConfigureContext *configContext = (WasmEdge_ConfigureContext *)configContextPointer;
    return WasmEdge_ConfigureStatisticsIsTimeMeasuring(configContext);
}
