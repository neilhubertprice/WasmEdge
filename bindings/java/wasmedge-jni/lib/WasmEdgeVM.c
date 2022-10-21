//
// Created by Kenvi Zhu on 2021-10-10.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "wasmedge/wasmedge.h"
#include "jni.h"
#include "common.h"
#include "StoreContext.h"
#include "ConfigureContext.h"
#include "FunctionTypeContext.h"
#include "AstModuleContext.h"
#include "StatisticsContext.h"
#include "ImportObjectContext.h"
#include "string.h"

void setJavaIntValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    int int_val = WasmEdge_ValueGetI32(val);
    jclass val_clazz = (*env)->GetObjectClass(env, jobj);
    jmethodID val_setter = (*env)->GetMethodID(env, val_clazz, "setValue", "(I)V");
    (*env)->CallIntMethod(env, jobj, val_setter, int_val);
    checkAndHandleException(env, "Error setting int value");
}

void setJavaLongValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    int long_val = WasmEdge_ValueGetI64(val);
    jclass val_clazz = (*env)->GetObjectClass(env, jobj);
    jmethodID val_setter = (*env)->GetMethodID(env, val_clazz, "setValue", "(J)V");
    (*env)->CallLongMethod(env, jobj, val_setter, long_val);
    checkAndHandleException(env, "Error setting long value");
}

void setJavaFloatValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    float float_val = WasmEdge_ValueGetF32(val);
    jclass val_clazz = (*env)->GetObjectClass(env, jobj);
    jmethodID val_setter = (*env)->GetMethodID(env, val_clazz, "setValue", "(F)V");
    (*env)->CallFloatMethod(env, jobj, val_setter, float_val);
    checkAndHandleException(env, "Error setting float value");
}

void setJavaDoubleValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    float double_val = WasmEdge_ValueGetF64(val);
    jclass val_clazz = (*env)->GetObjectClass(env, jobj);
    jmethodID val_setter = (*env)->GetMethodID(env, val_clazz, "setValue", "(D)V");
    (*env)->CallFloatMethod(env, jobj, val_setter, double_val);
    checkAndHandleException(env, "Error setting double value");
}

void setJavaStringValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    char* key = WasmEdge_ValueGetExternRef(val);
    jclass val_clazz = (*env)->GetObjectClass(env, jobj);

    jmethodID  val_setter = (*env)->GetMethodID(env, val_clazz, "setValue", "(Ljava/lang/String;)V");

    jstring jkey = (*env)->NewStringUTF(env, key);
    (*env)->CallObjectMethod(env, jobj, val_setter, jkey);
    checkAndHandleException(env, "Error setting string value");
}

jobject createDoubleJavaLongValueObject(JNIEnv *env, WasmEdge_Value val) {
    float double_val = WasmEdge_ValueGetF64(val);
    jclass val_clazz = (*env)->FindClass(env, "org/wasmedge/WasmEdgeF64Value");
    jmethodID val_constructor = (*env)->GetMethodID(env, val_clazz, "<init>", "(D)V");
    jobject j_val = (*env)->NewObject(env, val_clazz, val_constructor, double_val);
    return j_val;
}



WasmEdge_VMContext* getVmContext(JNIEnv* env, jobject vmContextObj) {
    long pointerVal = getPointer(env, vmContextObj);
    return (WasmEdge_VMContext*) pointerVal;
}


JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_runWasmFromFile
        (JNIEnv *env, jobject this_object, jstring file_path, jstring jFuncName,
         jobjectArray params, jint param_size, jintArray param_types, jobjectArray returns, jint return_size,
         jintArray return_types) {


    /* The configure and store context to the VM creation can be NULL. */
    WasmEdge_VMContext *VMCxt = getVmContext(env, this_object);

    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);


    /* The parameters and returns arrays. */
    WasmEdge_Value *wasm_params = parseJavaParams(env, params, param_types, param_size);
    WasmEdge_Value *Returns = malloc(sizeof(WasmEdge_Value) * return_size);

    const char *c_file_path = (*env)->GetStringUTFChars(env, file_path, NULL);

    /* Run the WASM function from file. */
    WasmEdge_Result Res = WasmEdge_VMRunWasmFromFile(VMCxt, c_file_path, wFuncName, wasm_params, param_size, Returns, return_size);

    handleWasmEdgeResult(env, &Res);
    if (WasmEdge_ResultOK(Res)) {
        for (int i = 0; i < return_size; ++i) {
            jobject jObj = (*env)->GetObjectArrayElement(env, returns, i);
            checkException(env, "Error retrieving returned item");
            setJavaValueObject(env, Returns[i], jObj);
        }
    } else {
        char exceptionBuffer[1024];
        sprintf(exceptionBuffer, "Error running wasm from file %s, error message: %s.", c_file_path,
                WasmEdge_ResultGetMessage(Res));

        (*env)->ThrowNew(env, (*env)->FindClass(env, "java/lang/Exception"),
                         exceptionBuffer);
    }


    /* Resources deallocations. */
    WasmEdge_StringDelete(wFuncName);
    (*env)->ReleaseStringUTFChars(env, file_path, c_file_path);
    free(wasm_params);
    free(Returns);
    return;
}

JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_nativeInit
        (JNIEnv * env, jobject thisObject, jlong configContextPointer, jlong storeContextPointer) {
    WasmEdge_ConfigureContext *ConfigureContext = (WasmEdge_ConfigureContext *)configContextPointer;
    WasmEdge_StoreContext *StoreContext = (WasmEdge_StoreContext *)storeContextPointer;

    WasmEdge_VMContext* VMContext = WasmEdge_VMCreate(ConfigureContext, StoreContext);

    setPointer(env, thisObject, (jlong)VMContext);
}

JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_loadWasmFromFile
        (JNIEnv * env, jobject thisObject, jstring filePath) {
    const char *c_file_path = (*env)->GetStringUTFChars(env, filePath, NULL);
    
    WasmEdge_Result res = WasmEdge_VMLoadWasmFromFile(getVmContext(env, thisObject), c_file_path);
    handleWasmEdgeResult(env, &res);

    (*env)->ReleaseStringUTFChars(env, filePath, c_file_path);
}


JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_validate
        (JNIEnv *env, jobject thisObject) {
    WasmEdge_Result result =  WasmEdge_VMValidate(getVmContext(env, thisObject));
    handleWasmEdgeResult(env, &result);
}

JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_instantiate
        (JNIEnv *env, jobject thisObject) {
    WasmEdge_Result result = WasmEdge_VMInstantiate(getVmContext(env, thisObject));
    handleWasmEdgeResult(env, &result);
}

JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_execute
        (JNIEnv *env, jobject thisObject, jstring jFuncName, jobjectArray params, jint paramSize,
         jintArray paramTypes, jobjectArray returns, jint returnSize, jintArray returnTypes) {

    WasmEdge_VMContext *VMCxt = getVmContext(env, thisObject);

    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);


    /* The parameters and returns arrays. */
    WasmEdge_Value *wasm_params = parseJavaParams(env, params, paramTypes, paramSize);
    WasmEdge_Value *Returns = malloc(sizeof(WasmEdge_Value) * returnSize);

    /* Run the WASM function from file. */
    WasmEdge_Result Res = WasmEdge_VMExecute(VMCxt, wFuncName, wasm_params, paramSize, Returns, returnSize);

    handleWasmEdgeResult(env, &Res);
    if (WasmEdge_ResultOK(Res)) {
        for (int i = 0; i < returnSize; ++i) {
            jobject jObj = (*env)->GetObjectArrayElement(env, returns, i);
            checkException(env, "Error retrieving returned item");
            setJavaValueObject(env, Returns[i], jObj);
        }
    }

    /* Resources deallocations. */
    WasmEdge_StringDelete(wFuncName);
    free(wasm_params);
    free(Returns);
    return;
}


JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_delete
        (JNIEnv * env, jobject thisObj) {
    WasmEdge_VMDelete(getVmContext(env, thisObj));
}


JNIEXPORT jint JNICALL Java_org_wasmedge_WasmEdgeVM_nativeGetFunctionListLength
        (JNIEnv *env , jobject thisObject) {
    WasmEdge_VMContext* vmContext = getVmContext(env, thisObject);

    return WasmEdge_VMGetFunctionListLength(vmContext);
}

JNIEXPORT jint JNICALL Java_org_wasmedge_WasmEdgeVM_nativeGetFunctionList
        (JNIEnv *env , jobject thisObject, jlongArray jPointersArray, jobjectArray jNamesArray, jint bufferLen) {
    WasmEdge_VMContext* vmContext = getVmContext(env, thisObject);

    const WasmEdge_FunctionTypeContext** funcList = (const WasmEdge_FunctionTypeContext**)malloc(sizeof (WasmEdge_FunctionTypeContext *) * bufferLen);
    WasmEdge_String* nameList = (WasmEdge_String*)malloc(sizeof (struct WasmEdge_String) * bufferLen);
    jint realFuncNum = WasmEdge_VMGetFunctionList(vmContext, nameList, funcList, bufferLen);

    jlong *funcPointers = (*env)->GetLongArrayElements(env, jPointersArray, NULL);

    for(int i = 0; i < realFuncNum; i++) {
        funcPointers[i] = (jlong)funcList[i];
        (*env)->SetObjectArrayElement(env, jNamesArray, i, WasmEdgeStringToJString(env, nameList[i]));
    }

    (*env)->ReleaseLongArrayElements(env, jPointersArray, funcPointers, 0);

    free(nameList);
    free(funcList);

    return realFuncNum;
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_WasmEdgeVM_nativeGetFunctionType
        (JNIEnv * env, jobject thisObject, jstring jFuncName) {
    WasmEdge_VMContext *vmContext = getVmContext(env, thisObject);

    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    const WasmEdge_FunctionTypeContext *functionTypeContext = WasmEdge_VMGetFunctionType(vmContext, wFuncName);

    WasmEdge_StringDelete(wFuncName);

    return (jlong)functionTypeContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_registerModuleFromFile
        (JNIEnv * env, jobject thisObject, jstring jModName, jstring jFilePath) {
    WasmEdge_VMContext * vmContext = getVmContext(env, thisObject);

    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    const char* filePath = (*env)->GetStringUTFChars(env, jFilePath, NULL);

    WasmEdge_Result result = WasmEdge_VMRegisterModuleFromFile(vmContext, wModName, filePath);

    (*env)->ReleaseStringUTFChars(env, jFilePath, filePath);
    WasmEdge_StringDelete(wModName);

    handleWasmEdgeResult(env, &result);
}

JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_registerModuleFromBuffer
        (JNIEnv * env, jobject thisObject, jstring jModName, jbyteArray jBuff) {

    WasmEdge_VMContext* vm = getVmContext(env, thisObject);

    jbyte* data = (*env)->GetByteArrayElements(env, jBuff, 0);
    checkException(env, "Error retrieving byte array");
    jsize size = (*env)->GetArrayLength(env, jBuff);

    WasmEdge_String wModName = JStringToWasmString(env, jModName);

    WasmEdge_VMRegisterModuleFromBuffer(vm, wModName, (uint8_t *)data, size);
    
    (*env)->ReleaseByteArrayElements(env, jBuff, data, 0);
    WasmEdge_StringDelete(wModName);
}


JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_registerModuleFromASTModule
        (JNIEnv * env, jobject thisObject, jstring jModName, jobject jAstModuleContext) {
    WasmEdge_VMContext * vmContext = getVmContext(env, thisObject);

    WasmEdge_ASTModuleContext * mod = getASTModuleContext(env, jAstModuleContext);
   
    WasmEdge_String wModName = JStringToWasmString(env, jModName);

    WasmEdge_Result result = WasmEdge_VMRegisterModuleFromASTModule(vmContext, wModName, mod);

    WasmEdge_StringDelete(wModName);

    handleWasmEdgeResult(env, &result);
}


JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_runWasmFromBuffer
        (JNIEnv * env, jobject thisObject, jbyteArray jBuff, jstring jFuncName,
         jobjectArray jParams, jintArray jParamTypes, jobjectArray jReturns,
         jintArray jReturnTypes) {

    WasmEdge_VMContext *vmContext = getVmContext(env, thisObject);

    jbyte* buff = (*env)->GetByteArrayElements(env, jBuff, 0);
    jsize size = (*env)->GetArrayLength(env, jBuff);
    
    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    /* The parameters and returns arrays. */
    jsize paramLen = (*env)->GetArrayLength(env, jParams);
    WasmEdge_Value *wasm_params = parseJavaParams(env, jParams, jParamTypes, paramLen);

    jsize returnLen = (*env)->GetArrayLength(env, jReturns);
    WasmEdge_Value *returns = malloc(sizeof(WasmEdge_Value) * returnLen);

    WasmEdge_Result result = WasmEdge_VMRunWasmFromBuffer(vmContext, (uint8_t *)buff, size, wFuncName, wasm_params, paramLen, returns, returnLen);

    handleWasmEdgeResult(env, &result);
    if (WasmEdge_ResultOK(result)) {
        for (int i = 0; i < returnLen; ++i) {
            jobject jObj = (*env)->GetObjectArrayElement(env, jReturns, i);
            checkException(env, "Error retrieving returned item");
            setJavaValueObject(env, returns[i], jObj);
        }
    }

    // release resources
    (*env)->ReleaseByteArrayElements(env, jBuff, buff, 0);
    WasmEdge_StringDelete(wFuncName);
    free(returns);
    free(wasm_params);
}


JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_runWasmFromASTModule
        (JNIEnv * env, jobject thisObject, jobject jAstMod, jstring jFuncName,
        jobjectArray jParams, jintArray jParamTypes, jobjectArray jReturns,
        jintArray jReturnTypes) {

    WasmEdge_VMContext *vmContext = getVmContext(env, thisObject);
    WasmEdge_ASTModuleContext * mod = getASTModuleContext(env, jAstMod);
    
    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    /* The parameters and returns arrays. */
    jsize paramLen = (*env)->GetArrayLength(env, jParams);
    WasmEdge_Value *wasm_params = parseJavaParams(env, jParams, jParamTypes, paramLen);

    jsize returnLen = (*env)->GetArrayLength(env, jReturns);
    WasmEdge_Value *returns = malloc(sizeof(WasmEdge_Value) * returnLen);

    WasmEdge_Result result = WasmEdge_VMRunWasmFromASTModule(vmContext, mod, wFuncName, wasm_params, paramLen, returns, returnLen);

    handleWasmEdgeResult(env, &result);
    if (WasmEdge_ResultOK(result)) {
        for (int i = 0; i < returnLen; ++i) {
            jobject jObj = (*env)->GetObjectArrayElement(env, jReturns, i);
            checkException(env, "Error retrieving returned item");
            setJavaValueObject(env, returns[i], jObj);
        }
    }

    // release resources
    WasmEdge_StringDelete(wFuncName);
    free(returns);
    free(wasm_params);
}

JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_executeRegistered
        (JNIEnv * env, jobject thisObject, jstring jModName, jstring jFuncName,
        jobjectArray jParams, jintArray jParamTypes, jobjectArray jReturns, jintArray jReturnTypes) {
    WasmEdge_VMContext * vmContext = getVmContext(env, thisObject);


    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    /* The parameters and returns arrays. */
    jsize paramLen = (*env)->GetArrayLength(env, jParams);
    WasmEdge_Value *wasm_params = parseJavaParams(env, jParams, jParamTypes, paramLen);

    jsize returnLen = (*env)->GetArrayLength(env, jReturns);
    WasmEdge_Value *returns = malloc(sizeof(WasmEdge_Value) * returnLen);

    WasmEdge_Result result = WasmEdge_VMExecuteRegistered(vmContext, wModName, wFuncName,
    								wasm_params, paramLen, returns, returnLen);

    handleWasmEdgeResult(env, &result);
    if (WasmEdge_ResultOK(result)) {
        for (int i = 0; i < returnLen; ++i) {
            jobject jObj = (*env)->GetObjectArrayElement(env, jReturns, i);
            checkException(env, "Error retrieving returned item");
            setJavaValueObject(env, returns[i], jObj);
        }
    }

    //release resources
    WasmEdge_StringDelete(wModName);
    WasmEdge_StringDelete(wFuncName);
    free(returns);
    free(wasm_params);
}

JNIEXPORT jlong JNICALL Java_org_wasmedge_WasmEdgeVM_nativeGetStoreContext
        (JNIEnv * env, jobject thisObject) {
    WasmEdge_VMContext *vmContext = getVmContext(env, thisObject);
    WasmEdge_StoreContext *storeContext = WasmEdge_VMGetStoreContext(vmContext);
    return (jlong)storeContext;
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_WasmEdgeVM_getStatisticsContext
        (JNIEnv * env, jobject thisObject) {

    WasmEdge_VMContext * vmContext = getVmContext(env, thisObject);
    WasmEdge_StatisticsContext *statCxt = WasmEdge_VMGetStatisticsContext(vmContext);
    return CreateJavaStatisticsContext(env, statCxt);
}

JNIEXPORT jobject JNICALL Java_org_wasmedge_WasmEdgeVM_nativeGetImportModuleContext
        (JNIEnv *env, jobject thisObject, jint reg) {
    WasmEdge_VMContext * vmContext = getVmContext(env, thisObject);
    WasmEdge_ImportObjectContext* imp = WasmEdge_VMGetImportModuleContext(vmContext, (enum WasmEdge_HostRegistration)reg);

    return createJImportObject(env, imp);
}


JNIEXPORT jlong JNICALL Java_org_wasmedge_WasmEdgeVM_nativeGetFunctionTypeRegistered
        (JNIEnv *env, jobject thisObject, jstring jModName, jstring jFuncName) {
    WasmEdge_VMContext * vmCxt = getVmContext(env, thisObject);
    WasmEdge_String wModName = JStringToWasmString(env, jModName);
    WasmEdge_String wFuncName = JStringToWasmString(env, jFuncName);

    const WasmEdge_FunctionTypeContext* functionTypeContext = WasmEdge_VMGetFunctionTypeRegistered(vmCxt, wModName, wFuncName);

    WasmEdge_StringDelete(wModName);
    WasmEdge_StringDelete(wFuncName);

    return (jlong)functionTypeContext;
}

JNIEXPORT void JNICALL Java_org_wasmedge_WasmEdgeVM_registerModuleFromImport
        (JNIEnv * env, jobject thisObject, jobject jImport) {
    WasmEdge_ImportObjectContext * impObj = getImportObjectContext(env, jImport);


    WasmEdge_VMContext *vm = getVmContext(env, thisObject);

    WasmEdge_Result result = WasmEdge_VMRegisterModuleFromImport(vm, impObj);
    handleWasmEdgeResult(env, &result);
}
