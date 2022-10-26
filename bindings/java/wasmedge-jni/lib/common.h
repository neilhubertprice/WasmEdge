//
// Created by Kenvi Zhu on 2021-11-09.
//

#ifndef WASMEDGE_JAVA_COMMON_H
#define WASMEDGE_JAVA_COMMON_H

#include "jni.h"
#include "wasmedge/wasmedge.h"

#define MAX_BUF_LEN 1024

enum ErrorCode {
    JVM_ERROR,
    WVM_ERROR
};

jstring call_Class_getName(JNIEnv *env, jclass clsObj);
jclass call_Object_getClass(JNIEnv *env, jobject obj);

void exitWithError(enum ErrorCode error, char* message);

void throwNoClassDefError(JNIEnv *env, char * message);
void throwNoSuchMethodError(JNIEnv *env, char* methodName, char* sig);

jint call_WasmEdgeI32Value_getValue(JNIEnv *env, jobject val);
jlong call_WasmEdgeI64Value_getValue(JNIEnv *env, jobject val);
jfloat call_WasmEdgeF32Value_getValue(JNIEnv *env, jobject val);
jdouble call_WasmEdgeF64Value_getValue(JNIEnv *env, jobject val);

void call_WasmEdgeI32Value_setValue(JNIEnv *env, jobject obj, jint val);
void call_WasmEdgeI64Value_setValue(JNIEnv *env, jobject obj, jlong val);
void call_WasmEdgeF32Value_setValue(JNIEnv *env, jobject obj, jfloat val);
void call_WasmEdgeF64Value_setValue(JNIEnv *env, jobject obj, jdouble val);

jstring call_WasmEdgeExternRef_getValue(JNIEnv *env, jobject val);
void call_WasmEdgeExternRef_setValue(JNIEnv *env, jobject obj, jstring val);

jobject construct_WasmEdgeI32Value(JNIEnv *env);
jobject construct_WasmEdgeI64Value(JNIEnv *env);
jobject construct_WasmEdgeF32Value(JNIEnv *env);
jobject construct_WasmEdgeF64Value(JNIEnv *env);
jobject construct_WasmEdgeExternRef(JNIEnv *env);
jobject construct_WasmEdgeFuncRef(JNIEnv *env);

jobject construct_WasmEdgeI32Value_withParam(JNIEnv *env, jint val);
jobject construct_WasmEdgeI64Value_withParam(JNIEnv *env, jlong val);
jobject construct_WasmEdgeF32Value_withParam(JNIEnv *env, jfloat val);
jobject construct_WasmEdgeF64Value_withParam(JNIEnv *env, jdouble val);

void setJavaIntValue(JNIEnv *env, WasmEdge_Value val, jobject jobj);
void setJavaLongValue(JNIEnv *env, WasmEdge_Value val, jobject jobj);
void setJavaFloatValue(JNIEnv *env, WasmEdge_Value val, jobject jobj);
void setJavaDoubleValue(JNIEnv *env, WasmEdge_Value val, jobject jobj);

char* getExternRefStringVal(JNIEnv *env, jobject val);
void setExternRefStringVal(JNIEnv *env, WasmEdge_Value val, jobject jobj);

jboolean call_List_add(JNIEnv *env, jobject jList, jobject ele);
jobject call_List_get(JNIEnv* env, jobject jList, jint idx);
jint call_List_size(JNIEnv* env, jobject jList);
jobject construct_ArrayList(JNIEnv *env, jint size);

jobject call_WasmEdgeValue_getType(JNIEnv *env, jobject obj);
jint call_ValueType_getValue(JNIEnv *env, jobject obj);
jobject call_ValueType_static_parseType(JNIEnv *env, jint value);

jobject construct_WasmEdgeLimit(JNIEnv *env, jboolean hasMax, jlong min, jlong max);

jobject call_FunctionInstanceContext_static_callHostFunction(JNIEnv *env, jlong funcKey, jlong memContextpointer,
        jobject paramList, jobject returnList);

jboolean call_Result_isSuccess(JNIEnv *env, jobject result);
jboolean call_Result_isTerminate(JNIEnv *env, jobject result);

void getClassName(JNIEnv* env, jobject obj, char* buff);

void handleWasmEdgeResult(JNIEnv* env, WasmEdge_Result * result);

// The returned array needs freeing once no longer used
WasmEdge_Value *parseJavaParams(JNIEnv *env, jobjectArray params, jintArray paramTypes, jint paramSize);

enum WasmEdge_ValType *parseValueTypes(JNIEnv *env, jintArray jValueTypes);
enum WasmEdge_ValType *parseValueTypesWithLen(JNIEnv *env, jintArray jValueTypes, jint len);

bool checkException(JNIEnv *env, const char* msg);

bool checkAndHandleException(JNIEnv *env, const char* msg);

void setJavaValueObject(JNIEnv *env, WasmEdge_Value value, jobject j_val);

jobject WasmEdgeStringArrayToJavaList(JNIEnv* env, WasmEdge_String* wStrList, int32_t len);

jstring WasmEdgeStringToJString(JNIEnv* env, WasmEdge_String wStr);

// Call 'free' on the returned string when no longer needed
char *JStringToCString(JNIEnv *env, jstring jstr);

// Call 'WasmEdge_StringDelete' on the returned string when no longer needed
WasmEdge_String JStringToWasmString(JNIEnv* env, jstring jstr);

// All strings in the array need releasing with ReleaseStringUTFCHars
const char** JStringArrayToPtrArray(JNIEnv* env, jarray jStrArray);

// Non-functional currently
void ReleasePtrArray(JNIEnv* env, jarray jStrArray, const char** ptr);

#endif //WASMEDGE_JAVA_COMMON_H
