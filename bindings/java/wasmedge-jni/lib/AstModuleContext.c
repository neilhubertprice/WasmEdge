//
// Created by Kenvi Zhu on 2021-12-20.
//
#include <stdlib.h>
#include "wasmedge/wasmedge.h"
#include "jni.h"
#include "common.h"
#include "ExportTypeContext.h"
#include "ImportTypeContext.h"

JNIEXPORT jobject JNICALL Java_org_wasmedge_ASTModuleContext_nativeListImports
        (JNIEnv * env, jobject thisObject, jlong astmContextPointer) {
    WasmEdge_ASTModuleContext *cxt = (WasmEdge_ASTModuleContext *)astmContextPointer;
    uint32_t len = WasmEdge_ASTModuleListImportsLength(cxt);

    const WasmEdge_ImportTypeContext **pEdgeImportTypeContext = malloc(sizeof(struct  WasmEdge_ImportTypeContext *) * len);

    WasmEdge_ASTModuleListImports(cxt, pEdgeImportTypeContext, len);

    jobject importList = CreateJavaArrayList(env, len);
    for (int i = 0; i < len; ++i) {
        AddElementToJavaList(env, importList, createImportTypeContext(env, pEdgeImportTypeContext[i], thisObject));
    }

    free(pEdgeImportTypeContext);

    return importList;
}

JNIEXPORT jlongArray JNICALL Java_org_wasmedge_ASTModuleContext_nativeListExports
        (JNIEnv *env, jobject thisObject, jlong astmContextPointer) {
    WasmEdge_ASTModuleContext *cxt = (WasmEdge_ASTModuleContext *)astmContextPointer;
    uint32_t len = WasmEdge_ASTModuleListExportsLength(cxt);

    const WasmEdge_ExportTypeContext **pExportTypeContext= malloc(sizeof(struct  WasmEdge_ExportTypeContext *) * len);

    WasmEdge_ASTModuleListExports(cxt, pExportTypeContext, len);

    jlongArray exportTypeArray = (*env)->NewLongArray(env, len);
    long *exportTypeData = (*env)->GetLongArrayElements(env, exportTypeArray, NULL);

    for (int i = 0; i < len; ++i) {
        exportTypeData[i] = (jlong)pExportTypeContext[i];
    }

    (*env)->ReleaseLongArrayElements(env, exportTypeArray, exportTypeData, 0);

    free(pExportTypeContext);

    return exportTypeArray;
}

JNIEXPORT void JNICALL Java_org_wasmedge_ASTModuleContext_nativeDelete
        (JNIEnv * env, jobject thisObject, jlong astmContextPointer) {
    WasmEdge_ASTModuleContext *mod = (WasmEdge_ASTModuleContext *)astmContextPointer;
    WasmEdge_ASTModuleDelete(mod);
}
