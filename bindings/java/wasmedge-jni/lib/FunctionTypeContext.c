//
// Created by Kenvi Zhu on 2021-12-04.
//
#include <stdlib.h>
#include "common.h"
#include "wasmedge/wasmedge.h"


jobject ConvertToJavaFunctionType(JNIEnv* env, const WasmEdge_FunctionTypeContext* functionTypeContext, const WasmEdge_String name);

JNIEXPORT jlong JNICALL Java_org_wasmedge_FunctionTypeContext_nativeInit
        (JNIEnv * env, jobject thisObject, jintArray paramTypes, jintArray returnTypes) {
    int paramLen = paramTypes ==  NULL ? 0 : (*env)->GetArrayLength(env, paramTypes);
    int returnLen = returnTypes == NULL? 0 : (*env)->GetArrayLength(env, returnTypes);
    enum WasmEdge_ValType* paramList = parseValueTypesWithLen(env, paramTypes, paramLen);
    enum WasmEdge_ValType* returnList = parseValueTypesWithLen(env, returnTypes, returnLen);

    WasmEdge_FunctionTypeContext * functionTypeContext =
            WasmEdge_FunctionTypeCreate(paramList, paramLen, returnList, returnLen);
    
    return (jlong)functionTypeContext;
}

JNIEXPORT jintArray JNICALL Java_org_wasmedge_FunctionTypeContext_nativeGetParameters
        (JNIEnv *env, jobject thisObject, jlong funcTypePointer) {
    WasmEdge_FunctionTypeContext *functionTypeContext = (WasmEdge_FunctionTypeContext *)funcTypePointer;
    uint32_t paramLen = WasmEdge_FunctionTypeGetParametersLength(functionTypeContext);
    enum WasmEdge_ValType* params = malloc(sizeof (enum WasmEdge_ValType) * paramLen);
    WasmEdge_FunctionTypeGetParameters(functionTypeContext, params, paramLen);

    jintArray types = (*env)->NewIntArray(env, paramLen);
    (*env)->SetIntArrayRegion(env, types, 0, paramLen, (jint*) params);
    free(params);
    return types;
}


JNIEXPORT jintArray JNICALL Java_org_wasmedge_FunctionTypeContext_nativeGetReturns
        (JNIEnv * env, jobject thisObject, jlong funcTypePointer){
    WasmEdge_FunctionTypeContext *functionTypeContext = (WasmEdge_FunctionTypeContext *)funcTypePointer;
    uint32_t returnLen = WasmEdge_FunctionTypeGetReturnsLength(functionTypeContext);
    enum WasmEdge_ValType* returns = malloc(sizeof (enum  WasmEdge_ValType) * returnLen);
    WasmEdge_FunctionTypeGetReturns(functionTypeContext, returns, returnLen);

    jintArray types = (*env)->NewIntArray(env, returnLen);
    (*env)->SetIntArrayRegion(env, types, 0, returnLen, (jint*) returns);
    free(returns);
    return types;
}

JNIEXPORT void JNICALL Java_org_wasmedge_FunctionTypeContext_nativeDelete
        (JNIEnv * env, jobject thisObject, jlong funcTypePointer) {
    WasmEdge_FunctionTypeContext *functionTypeContext = (WasmEdge_FunctionTypeContext *)funcTypePointer;
    WasmEdge_FunctionTypeDelete(functionTypeContext);
}

jobject ConvertToJavaValueType(JNIEnv* env, enum WasmEdge_ValType* valType) {

    jclass  valueTypeCalss = findJavaClass(env, "org/wasmedge/enums/ValueType");
    if(valueTypeCalss == NULL) {
        return NULL;
    }

    jmethodID jmethodId = (*env)->GetStaticMethodID(env, valueTypeCalss, "parseType", "(I)Lorg/wasmedge/enums/ValueType;");

    if(jmethodId == NULL) {
        return NULL;
    }

    jobject  valueType = (*env)->CallStaticObjectMethod(env, valueTypeCalss, jmethodId, (jint)*valType);

    if(checkAndHandleException(env, "Error when creating value type")) {
        return NULL;
    }

    return valueType;
}



jobject ConvertToValueTypeList(JNIEnv* env, enum WasmEdge_ValType* list, int32_t len) {
    jclass listClass = findJavaClass(env, "java/util/ArrayList");

    if (listClass == NULL) {
        return NULL;
    }

    jmethodID listConstructor = findJavaMethod(env, listClass, "<init>", "(I)V");

    if(listConstructor == NULL) {
        return NULL;
    }

    jobject jList = (*env)->NewObject(env, listClass, listConstructor, len);

    if(jList == NULL) {
        return NULL;
    }

    if(checkAndHandleException(env, "Error when creating value type list")) {
        return NULL;
    }

    char buf[256];
    getClassName(env, jList, buf);


    jmethodID addMethod = findJavaMethod(env, listClass, "add", "(Ljava/lang/Object;)Z");

    if(addMethod == NULL) {
        return NULL;
    }

    enum WasmEdge_ValType* ptr = list;
    for (int i = 0; i < len; ++i) {
        jobject valueType = ConvertToJavaValueType(env, ptr);

        (*env)->CallBooleanMethod(env, jList, addMethod, valueType);

        if(checkAndHandleException(env, "Error when adding value type")) {
            return NULL;
        }

        ptr++;
    }

    return jList;

}
