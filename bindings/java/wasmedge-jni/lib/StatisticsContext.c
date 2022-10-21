//
// Created by Kenvi Zhu on 2022-01-09.
//
#include <stdlib.h>
#include "jni.h"
#include "wasmedge/wasmedge.h"
#include "common.h"

JNIEXPORT jlong JNICALL Java_org_wasmedge_StatisticsContext_nativeInit
        (JNIEnv * env, jobject thisObject) {
    WasmEdge_StatisticsContext *statCxt = WasmEdge_StatisticsCreate();
    return (jlong)statCxt;
}

JNIEXPORT jint JNICALL Java_org_wasmedge_StatisticsContext_nativeGetInstrCount
        (JNIEnv * env, jobject thisObject, jlong statContextPointer) {
    WasmEdge_StatisticsContext* statCxt = (WasmEdge_StatisticsContext *)statContextPointer;
    return WasmEdge_StatisticsGetInstrCount(statCxt);
}

JNIEXPORT jdouble JNICALL Java_org_wasmedge_StatisticsContext_nativeGetInstrPerSecond
        (JNIEnv * env, jobject thisObject, jlong statContextPointer) {
    WasmEdge_StatisticsContext* statCxt = (WasmEdge_StatisticsContext *)statContextPointer;
    return WasmEdge_StatisticsGetInstrPerSecond(statCxt);
}

JNIEXPORT void JNICALL Java_org_wasmedge_StatisticsContext_nativeSetCostTable
        (JNIEnv * env, jobject thisObject, jlong statContextPointer, jlongArray jCostTable) {
    WasmEdge_StatisticsContext* statCxt = (WasmEdge_StatisticsContext *)statContextPointer;

    int len = (*env)->GetArrayLength(env, jCostTable);
    long* data = (*env)->GetLongArrayElements(env, jCostTable, NULL);

    WasmEdge_StatisticsSetCostTable(statCxt, (uint64_t *)data, len);

    (*env)->ReleaseLongArrayElements(env, jCostTable, data, 0);
}

JNIEXPORT void JNICALL Java_org_wasmedge_StatisticsContext_nativeSetCostLimit
        (JNIEnv * env, jobject thisObject, jlong statContextPointer, jlong costLimit) {
    WasmEdge_StatisticsContext* statCxt = (WasmEdge_StatisticsContext *)statContextPointer;
    WasmEdge_StatisticsSetCostLimit(statCxt, costLimit);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_StatisticsContext_nativeGetTotalCost
        (JNIEnv * env, jobject thisObject, jlong statContextPointer) {
    WasmEdge_StatisticsContext* statCxt = (WasmEdge_StatisticsContext *)statContextPointer;
    return WasmEdge_StatisticsGetTotalCost(statCxt);
}

JNIEXPORT void JNICALL Java_org_wasmedge_StatisticsContext_nativeDelete
        (JNIEnv * env, jobject thisObject, jlong statContextPointer) {
    WasmEdge_StatisticsContext *statCxt = (WasmEdge_StatisticsContext *)statContextPointer;
    WasmEdge_StatisticsDelete(statCxt);
}

