//
// Created by Kenvi Zhu on 2021-11-09.
//
#include "common.h"
#include "jni.h"
#include <stdlib.h>
#include <string.h>
#include "wasmedge/wasmedge.h"

bool checkAndHandleException(JNIEnv *env, const char* msg);


static jint JNI_VERSION = JNI_VERSION_1_8;

static jclass JC_Object;
static jmethodID JMID_Object_getClass;
static jmethodID JMID_Object_toString;

static jclass JC_Class;
static jmethodID JMID_Class_getName;

static jclass JC_NoClassDefFoundError;
static jclass JC_NoSuchMethodError;
static jclass JC_Exception;
static jclass JC_RuntimeException;

static jclass JC_WasmEdgeI32Value;
static jclass JC_WasmEdgeI64Value;
static jclass JC_WasmEdgeF32Value;
static jclass JC_WasmEdgeF64Value;
static jmethodID JMID_WasmEdgeI32Value_getValue;
static jmethodID JMID_WasmEdgeI64Value_getValue;
static jmethodID JMID_WasmEdgeF32Value_getValue;
static jmethodID JMID_WasmEdgeF64Value_getValue;
static jmethodID JMID_WasmEdgeI32Value_setValue;
static jmethodID JMID_WasmEdgeI64Value_setValue;
static jmethodID JMID_WasmEdgeF32Value_setValue;
static jmethodID JMID_WasmEdgeF64Value_setValue;
static jmethodID JMID_WasmEdgeI32Value_constructor;
static jmethodID JMID_WasmEdgeI64Value_constructor;
static jmethodID JMID_WasmEdgeF32Value_constructor;
static jmethodID JMID_WasmEdgeF64Value_constructor;
static jmethodID JMID_WasmEdgeI32Value_constructorWithParam;
static jmethodID JMID_WasmEdgeI64Value_constructorWithParam;
static jmethodID JMID_WasmEdgeF32Value_constructorWithParam;
static jmethodID JMID_WasmEdgeF64Value_constructorWithParam;

static jclass JC_WasmEdgeExternRef;
static jclass JC_WasmEdgeFuncRef;
static jmethodID JMID_WasmEdgeExternRef_getValue;
static jmethodID JMID_WasmEdgeExternRef_setValue;
static jmethodID JMID_WasmEdgeExternRef_constructor;
static jmethodID JMID_WasmEdgeFuncRef_constructor;

static jclass JC_List;
static jclass JC_ArrayList;
static jmethodID JMID_List_add;
static jmethodID JMID_List_get;
static jmethodID JMID_List_size;
static jmethodID JMID_ArrayList_constructor;

static jclass JC_WasmEdgeValue;
static jclass JC_ValueType;
static jmethodID JMID_WasmEdgeValue_getType;
static jmethodID JMID_ValueType_getValue;
static jmethodID JMID_ValueType_static_parseType;

static jclass JC_WasmEdgeLimit;
static jmethodID JMID_WasmEdgeLimit_constructor;

static jclass JC_FunctionInstanceContext;
static jmethodID JMID_FunctionInstanceContext_static_callHostFunction;

static jclass JC_Result;
static jmethodID JMID_Result_isSuccess;
static jmethodID JMID_Result_isTerminate;

// Initialize the class and methodID lookups
jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    // Obtain the JNIEnv from the VM and confirm JNI_VERSION
    JNIEnv *env;
    if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION) != JNI_OK) {
        return JNI_ERR;
    }

    jclass tempLocalClassRef;

    ///// java.lang.Object
    tempLocalClassRef = (*env)->FindClass(env, "java/lang/Object");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_Object = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);
   
    JMID_Object_getClass = (*env)->GetMethodID(env, JC_Object, "getClass", "()Ljava/lang/Class;");
    JMID_Object_toString = (*env)->GetMethodID(env, JC_Object, "toString", "()Ljava/lang/String;");

    ///// java.lang.Class
    tempLocalClassRef = (*env)->FindClass(env, "java/lang/Class");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_Class = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);
    
    JMID_Class_getName = (*env)->GetMethodID(env, JC_Class, "getName", "()Ljava/lang/String;");

    ///// Exceptions
    tempLocalClassRef = (*env)->FindClass(env, "java/lang/NoClassDefFoundError");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_NoClassDefFoundError = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    tempLocalClassRef = (*env)->FindClass(env, "java/lang/NoSuchMethodError");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_NoSuchMethodError = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    tempLocalClassRef = (*env)->FindClass(env, "java/lang/Exception");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_Exception = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    tempLocalClassRef = (*env)->FindClass(env, "java/lang/RuntimeException");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_RuntimeException = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);


    ///// WasmEdgeValue classes
    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/WasmEdgeI32Value");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_WasmEdgeI32Value = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);
 
    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/WasmEdgeI64Value");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_WasmEdgeI64Value = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/WasmEdgeF32Value");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_WasmEdgeF32Value = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);
 
    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/WasmEdgeF64Value");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_WasmEdgeF64Value = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);
    
    JMID_WasmEdgeI32Value_getValue = (*env)->GetMethodID(env, JC_WasmEdgeI32Value, "getValue", "()I");
    JMID_WasmEdgeI64Value_getValue = (*env)->GetMethodID(env, JC_WasmEdgeI64Value, "getValue", "()J");
    JMID_WasmEdgeF32Value_getValue = (*env)->GetMethodID(env, JC_WasmEdgeF32Value, "getValue", "()F");
    JMID_WasmEdgeF64Value_getValue = (*env)->GetMethodID(env, JC_WasmEdgeF64Value, "getValue", "()D");

    JMID_WasmEdgeI32Value_setValue = (*env)->GetMethodID(env, JC_WasmEdgeI32Value, "setValue", "(I)V");
    JMID_WasmEdgeI64Value_setValue = (*env)->GetMethodID(env, JC_WasmEdgeI64Value, "setValue", "(J)V");
    JMID_WasmEdgeF32Value_setValue = (*env)->GetMethodID(env, JC_WasmEdgeF32Value, "setValue", "(F)V");
    JMID_WasmEdgeF64Value_setValue = (*env)->GetMethodID(env, JC_WasmEdgeF64Value, "setValue", "(D)V");

    JMID_WasmEdgeI32Value_constructor = (*env)->GetMethodID(env, JC_WasmEdgeI32Value, "<init>", "()V");
    JMID_WasmEdgeI64Value_constructor = (*env)->GetMethodID(env, JC_WasmEdgeI64Value, "<init>", "()V");
    JMID_WasmEdgeF32Value_constructor = (*env)->GetMethodID(env, JC_WasmEdgeF32Value, "<init>", "()V");
    JMID_WasmEdgeF64Value_constructor = (*env)->GetMethodID(env, JC_WasmEdgeF64Value, "<init>", "()V");

    JMID_WasmEdgeI32Value_constructorWithParam = (*env)->GetMethodID(env, JC_WasmEdgeI32Value, "<init>", "(I)V");
    JMID_WasmEdgeI64Value_constructorWithParam = (*env)->GetMethodID(env, JC_WasmEdgeI64Value, "<init>", "(J)V");
    JMID_WasmEdgeF32Value_constructorWithParam = (*env)->GetMethodID(env, JC_WasmEdgeF32Value, "<init>", "(F)V");
    JMID_WasmEdgeF64Value_constructorWithParam = (*env)->GetMethodID(env, JC_WasmEdgeF64Value, "<init>", "(D)V");

    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/WasmEdgeExternRef");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_WasmEdgeExternRef = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/WasmEdgeFuncRef");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_WasmEdgeFuncRef = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    JMID_WasmEdgeExternRef_getValue = (*env)->GetMethodID(env, JC_WasmEdgeExternRef, "getValue", "()Ljava/lang/String;");
    JMID_WasmEdgeExternRef_setValue = (*env)->GetMethodID(env, JC_WasmEdgeExternRef, "setValue", "(Ljava/lang/String;)V");

    JMID_WasmEdgeExternRef_constructor = (*env)->GetMethodID(env, JC_WasmEdgeExternRef, "<init>", "()V");
    JMID_WasmEdgeFuncRef_constructor = (*env)->GetMethodID(env, JC_WasmEdgeFuncRef, "<init>", "()V");


    ///// List classes
    tempLocalClassRef = (*env)->FindClass(env, "java/util/List");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_List = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    tempLocalClassRef = (*env)->FindClass(env, "java/util/ArrayList");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_ArrayList = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);
    
    JMID_List_add = (*env)->GetMethodID(env, JC_List, "add", "(Ljava/lang/Object;)Z");
    JMID_List_get = (*env)->GetMethodID(env, JC_List, "get", "(I)Ljava/lang/Object;");
    JMID_List_size = (*env)->GetMethodID(env, JC_List, "size", "()I");

    JMID_ArrayList_constructor = (*env)->GetMethodID(env, JC_ArrayList, "<init>", "(I)V");


    ///// WasmEdgeValue
    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/WasmEdgeValue");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_WasmEdgeValue = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/enums/ValueType");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_ValueType = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    JMID_WasmEdgeValue_getType = (*env)->GetMethodID(env, JC_WasmEdgeValue, "getType", "()Lorg/wasmedge/enums/ValueType;");

    JMID_ValueType_getValue = (*env)->GetMethodID(env, JC_ValueType, "getValue", "()I");
    JMID_ValueType_static_parseType = (*env)->GetStaticMethodID(env, JC_ValueType, "parseType", "(I)Lorg/wasmedge/enums/ValueType;");


    ///// WasmEdgeLimit
    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/WasmEdgeLimit");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_WasmEdgeLimit = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    JMID_WasmEdgeLimit_constructor = (*env)->GetMethodID(env, JC_WasmEdgeLimit, "<init>", "(ZJJ)V");


    ///// FunctionInstanceContext
    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/FunctionInstanceContext");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_FunctionInstanceContext = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    JMID_FunctionInstanceContext_static_callHostFunction = (*env)->GetStaticMethodID(env, JC_FunctionInstanceContext, "callHostFunction", "(JJLjava/util/List;Ljava/util/List;)Lorg/wasmedge/Result;");


    ///// Result
    tempLocalClassRef = (*env)->FindClass(env, "org/wasmedge/Result");
    if (tempLocalClassRef == NULL) {
        return JNI_ERR;
    }
    JC_Result = (jclass) (*env)->NewGlobalRef(env, tempLocalClassRef);
    (*env)->DeleteLocalRef(env, tempLocalClassRef);

    JMID_Result_isSuccess = (*env)->GetMethodID(env, JC_Result, "isSuccess", "()Z");
    JMID_Result_isTerminate = (*env)->GetMethodID(env, JC_Result, "isTerminate", "()Z");


    return JNI_VERSION;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {
    // Obtain the JNIEnv from the VM
    JNIEnv* env;
    (*vm)->GetEnv(vm, (void **)&env, JNI_VERSION);

    // Destroy the global references
    (*env)->DeleteGlobalRef(env, JC_Class);
    (*env)->DeleteGlobalRef(env, JC_Object);

    (*env)->DeleteGlobalRef(env, JC_NoClassDefFoundError);
    (*env)->DeleteGlobalRef(env, JC_NoSuchMethodError);
    (*env)->DeleteGlobalRef(env, JC_Exception);
    (*env)->DeleteGlobalRef(env, JC_RuntimeException);

    (*env)->DeleteGlobalRef(env, JC_WasmEdgeI32Value);
    (*env)->DeleteGlobalRef(env, JC_WasmEdgeI64Value);
    (*env)->DeleteGlobalRef(env, JC_WasmEdgeF32Value);
    (*env)->DeleteGlobalRef(env, JC_WasmEdgeF64Value);
    (*env)->DeleteGlobalRef(env, JC_WasmEdgeExternRef);
    (*env)->DeleteGlobalRef(env, JC_WasmEdgeFuncRef);

    (*env)->DeleteGlobalRef(env, JC_List);
    (*env)->DeleteGlobalRef(env, JC_ArrayList);

    (*env)->DeleteGlobalRef(env, JC_WasmEdgeValue);
    (*env)->DeleteGlobalRef(env, JC_ValueType);

    (*env)->DeleteGlobalRef(env, JC_WasmEdgeLimit);

    (*env)->DeleteGlobalRef(env, JC_FunctionInstanceContext);

    (*env)->DeleteGlobalRef(env, JC_Result);
}

jstring call_Class_getName(JNIEnv *env, jclass clsObj) {
    jstring strObj = (jstring)(*env)->CallObjectMethod(env, clsObj, JMID_Class_getName);
    checkAndHandleException(env, "Class.getName() error");
    return strObj;
}

jclass call_Object_getClass(JNIEnv *env, jobject obj) {
    jclass clsObj = (jclass)(*env)->CallObjectMethod(env, obj, JMID_Object_getClass);
    checkAndHandleException(env, "Object.getClass() error");
    return clsObj;
}

jstring call_Object_toString(JNIEnv *env, jobject obj) {
    jstring strObj = (jstring)(*env)->CallObjectMethod(env, obj, JMID_Object_toString);
    checkAndHandleException(env, "Object.toString() error");
    return strObj;
}

void exitWithError(enum ErrorCode error, char* message) {
     exit(-1);
}

void throwNoClassDefError(JNIEnv *env, char * message) {
    (*env)->ThrowNew(env, JC_NoClassDefFoundError, message);
    exitWithError(JVM_ERROR, "Exception thrown for no class def");
}

void throwNoSuchMethodError(JNIEnv *env, char* methodName, char* sig) {
    (*env)->ThrowNew(env, JC_NoSuchMethodError, methodName);
    exitWithError(JVM_ERROR, "Exception thrown for no such method");
}


jint call_WasmEdgeI32Value_getValue(JNIEnv *env, jobject val) {
    jint value = (*env)->CallIntMethod(env, val, JMID_WasmEdgeI32Value_getValue);
    checkAndHandleException(env, "Error in I32 getValue()");
    return value;
}

jlong call_WasmEdgeI64Value_getValue(JNIEnv *env, jobject val) {
    jlong value = (*env)->CallLongMethod(env, val, JMID_WasmEdgeI64Value_getValue);
    checkAndHandleException(env, "Error in I64 getValue()");
    return value;
}

jfloat call_WasmEdgeF32Value_getValue(JNIEnv *env, jobject val) {
    jfloat value = (*env)->CallFloatMethod(env, val, JMID_WasmEdgeF32Value_getValue);
    checkAndHandleException(env, "Error in F32 getValue()");
    return value;
}

jdouble call_WasmEdgeF64Value_getValue(JNIEnv *env, jobject val) {
    jdouble value = (*env)->CallDoubleMethod(env, val, JMID_WasmEdgeF64Value_getValue);
    checkAndHandleException(env, "Error in F64 getValue()");
    return value;
}


void call_WasmEdgeI32Value_setValue(JNIEnv *env, jobject obj, jint val) {
    (*env)->CallIntMethod(env, obj, JMID_WasmEdgeI32Value_setValue, val);
    checkAndHandleException(env, "Error in I32 setValue()");
}

void call_WasmEdgeI64Value_setValue(JNIEnv *env, jobject obj, jlong val) {
    (*env)->CallLongMethod(env, obj, JMID_WasmEdgeI64Value_setValue, val);
    checkAndHandleException(env, "Error in I64 setValue()");
}

void call_WasmEdgeF32Value_setValue(JNIEnv *env, jobject obj, jfloat val) {
    (*env)->CallFloatMethod(env, obj, JMID_WasmEdgeF32Value_setValue, val);
    checkAndHandleException(env, "Error in F32 setValue()");
}

void call_WasmEdgeF64Value_setValue(JNIEnv *env, jobject obj, jdouble val) {
    (*env)->CallDoubleMethod(env, obj, JMID_WasmEdgeF64Value_setValue, val);
    checkAndHandleException(env, "Error in F64 setValue()");
}

jobject construct_WasmEdgeI32Value(JNIEnv *env) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeI32Value, JMID_WasmEdgeI32Value_constructor);
    return jVal;
}

jobject construct_WasmEdgeI64Value(JNIEnv *env) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeI64Value, JMID_WasmEdgeI64Value_constructor);
    return jVal;
}

jobject construct_WasmEdgeF32Value(JNIEnv *env) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeF32Value, JMID_WasmEdgeF32Value_constructor);
    return jVal;
}

jobject construct_WasmEdgeF64Value(JNIEnv *env) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeF64Value, JMID_WasmEdgeF64Value_constructor);
    return jVal;
}

jobject construct_WasmEdgeI32Value_withParam(JNIEnv *env, jint val) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeI32Value, JMID_WasmEdgeI32Value_constructorWithParam, val);
    return jVal;
}

jobject construct_WasmEdgeI64Value_withParam(JNIEnv *env, jlong val) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeI64Value, JMID_WasmEdgeI64Value_constructorWithParam, val);
    return jVal;
}

jobject construct_WasmEdgeF32Value_withParam(JNIEnv *env, jfloat val) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeF32Value, JMID_WasmEdgeF32Value_constructorWithParam, val);
    return jVal;
}

jobject construct_WasmEdgeF64Value_withParam(JNIEnv *env, jdouble val) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeF64Value, JMID_WasmEdgeF64Value_constructorWithParam, val);
    return jVal;
}


jstring call_WasmEdgeExternRef_getValue(JNIEnv *env, jobject val) {
    jstring value = (jstring)(*env)->CallObjectMethod(env, val, JMID_WasmEdgeExternRef_getValue);
    checkException(env, "Error in ExternRef getValue()");
    return value;
}

void call_WasmEdgeExternRef_setValue(JNIEnv *env, jobject obj, jstring val) {
    (*env)->CallObjectMethod(env, obj, JMID_WasmEdgeExternRef_setValue, val);
    checkAndHandleException(env, "Error in ExternRef setValue()");
}

jobject construct_WasmEdgeExternRef(JNIEnv *env) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeExternRef, JMID_WasmEdgeExternRef_constructor);
    return jVal;
}

jobject construct_WasmEdgeFuncRef(JNIEnv *env) {
    jobject jVal = (*env)->NewObject(env, JC_WasmEdgeFuncRef, JMID_WasmEdgeFuncRef_constructor);
    return jVal;
}

void setJavaIntValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    int int_val = WasmEdge_ValueGetI32(val);

    call_WasmEdgeI32Value_setValue(env, jobj, int_val);
}

void setJavaLongValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    int long_val = WasmEdge_ValueGetI64(val);

    call_WasmEdgeI64Value_setValue(env, jobj, long_val);
}

void setJavaFloatValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    float float_val = WasmEdge_ValueGetF32(val);

    call_WasmEdgeF32Value_setValue(env, jobj, float_val);
}

void setJavaDoubleValue(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    float double_val = WasmEdge_ValueGetF64(val);

    call_WasmEdgeF64Value_setValue(env, jobj, double_val);
}

char* getExternRefStringVal(JNIEnv *env, jobject val) {
    jstring value = call_WasmEdgeExternRef_getValue(env, val);
 
    return JStringToCString(env, value);
}

void setExternRefStringVal(JNIEnv *env, WasmEdge_Value val, jobject jobj) {
    char* key = WasmEdge_ValueGetExternRef(val);
    jstring jkey = (*env)->NewStringUTF(env, key);
    call_WasmEdgeExternRef_setValue(env, jobj, jkey);
}


jboolean call_List_add(JNIEnv *env, jobject jList, jobject ele) {
    jboolean retVal = (*env)->CallBooleanMethod(env, jList, JMID_List_add, ele);
    checkException(env, "Error calling List add()");
    return retVal;
}

jobject call_List_get(JNIEnv* env, jobject jList, jint idx) {
    jobject retVal = (*env)->CallObjectMethod(env, jList, JMID_List_get, idx);
    checkException(env, "Error calling List get()");
    return retVal;
}

jint call_List_size(JNIEnv* env, jobject jList) {
    jint size = (*env)->CallIntMethod(env, jList, JMID_List_size);
    checkException(env, "Error calling List size()");
    return size;
}

jobject construct_ArrayList(JNIEnv *env, jint size) {
    jobject jList = (*env)->NewObject(env, JC_ArrayList, JMID_ArrayList_constructor, size);
    if(checkAndHandleException(env, "Error when creating ArrayList")) {
        return NULL;
    }
    return jList;
}


jobject call_WasmEdgeValue_getType(JNIEnv *env, jobject obj) {
    jobject valType = (*env)->CallObjectMethod(env, obj, JMID_WasmEdgeValue_getType);
    checkException(env, "Error calling getType()");
    return valType;
}

jint call_ValueType_getValue(JNIEnv *env, jobject obj) {
    jint jType = (*env)->CallIntMethod(env, obj, JMID_ValueType_getValue);
    checkException(env, "Error calling getValue()");
    return jType;
}

jobject call_ValueType_static_parseType(JNIEnv *env, jint value) {
    jobject valueType = (*env)->CallStaticObjectMethod(env, JC_ValueType, JMID_ValueType_static_parseType, value);

    if(checkAndHandleException(env, "Error when creating value type")) {
        return NULL;
    }

    return valueType;
}

jobject construct_WasmEdgeLimit(JNIEnv *env, jboolean hasMax, jlong min, jlong max) {
    jobject jLimit = (*env)->NewObject(env, JC_WasmEdgeLimit, JMID_WasmEdgeLimit_constructor, hasMax, min, max);
    if(checkAndHandleException(env, "Error when creating WasmEdgeLimit")) {
        return NULL;
    }
    return jLimit;
}

jobject call_FunctionInstanceContext_static_callHostFunction(JNIEnv *env, jlong funcKey, jlong memContextpointer,
        jobject paramList, jobject returnList) {
    jobject result = (*env)->CallStaticObjectMethod(env, JC_FunctionInstanceContext, JMID_FunctionInstanceContext_static_callHostFunction,
            funcKey, memContextpointer, paramList, returnList);
    checkException(env, "Error calling callHostFunction");
    return result;
}

jboolean call_Result_isSuccess(JNIEnv *env, jobject result) {
    jboolean isSuccess = (*env)->CallBooleanMethod(env, result, JMID_Result_isSuccess);
    checkException(env, "Error calling isSuccess method");
    return isSuccess;
}

jboolean call_Result_isTerminate(JNIEnv *env, jobject result) {
    jboolean isTerminate = (*env)->CallBooleanMethod(env, result, JMID_Result_isTerminate);
    checkException(env, "Error calling isTerminate method");
    return isTerminate;
}


void getClassName(JNIEnv* env, jobject obj, char* buff) {
    jclass clsObj = call_Object_getClass(env, obj);
    jstring strObj = call_Class_getName(env, clsObj);

    const char* str = (*env)->GetStringUTFChars(env, strObj, NULL);
    strcpy(buff, str);
    (*env)->ReleaseStringUTFChars(env, strObj, str);

    (*env)->DeleteLocalRef(env, strObj);
    (*env)->DeleteLocalRef(env, clsObj);
}

void handleWasmEdgeResult(JNIEnv* env, WasmEdge_Result * result) {
    if(!WasmEdge_ResultOK(*result)) {
        char exceptionBuffer[1024];
        sprintf(exceptionBuffer, "Error occurred with message: %s.", WasmEdge_ResultGetMessage(*result));

        (*env)->ThrowNew(env, JC_Exception, exceptionBuffer);
    }
}


// The returned array needs freeing once no longer used
WasmEdge_Value *parseJavaParams(JNIEnv *env, jobjectArray params, jintArray paramTypes, jint paramSize) {

    WasmEdge_Value *wasm_params = calloc(paramSize, sizeof(WasmEdge_Value));
    int *type = (*env)->GetIntArrayElements(env, paramTypes, NULL);
    checkException(env, "Error getting param types");

    for (int i = 0; i < paramSize; i++) {
        WasmEdge_Value val;

        jobject val_object = (*env)->GetObjectArrayElement(env, params, i);
        checkException(env, "Error getting param");

        switch (type[i]) {
            case 0:
                val = WasmEdge_ValueGenI32(call_WasmEdgeI32Value_getValue(env, val_object));
                break;
            case 1:
                val = WasmEdge_ValueGenI64(call_WasmEdgeI64Value_getValue(env, val_object));
                break;
            case 2:
                val = WasmEdge_ValueGenF32(call_WasmEdgeF32Value_getValue(env, val_object));
                break;
            case 3:
                val = WasmEdge_ValueGenF64(call_WasmEdgeF64Value_getValue(env, val_object));
                break;
            case 4:
                //TODO
                val = WasmEdge_ValueGenV128(call_WasmEdgeI64Value_getValue(env, val_object));
                break;
            case 5:
                //TODO
                val = WasmEdge_ValueGenFuncRef(call_WasmEdgeI64Value_getValue(env, val_object));
                break;
            case 6:
                //TODO
                val = WasmEdge_ValueGenExternRef(getExternRefStringVal(env, val_object));
                break;
            default:
                break;
        }
        wasm_params[i] = val;

        (*env)->DeleteLocalRef(env, val_object);
    }

    (*env)->ReleaseIntArrayElements(env, paramTypes, type, 0);

    return wasm_params;
}


enum WasmEdge_ValType *parseValueTypes(JNIEnv *env, jintArray jValueTypes) {
    if(jValueTypes == NULL)  {
        return NULL;
    }

    jint len = (*env)->GetArrayLength(env, jValueTypes);
    return parseValueTypesWithLen(env, jValueTypes, len);
}

enum WasmEdge_ValType *parseValueTypesWithLen(JNIEnv *env, jintArray jValueTypes, jint len) {
    if(jValueTypes == NULL)  {
        return NULL;
    }

    enum WasmEdge_ValType* valTypes = malloc(len * sizeof(enum  WasmEdge_ValType));

    jint* elements = (*env)->GetIntArrayElements(env, jValueTypes, false);
    checkException(env, "Error getting value types");
    for (int i = 0; i < len; ++i) {
        valTypes[i] = elements[i];
    }

    (*env)->ReleaseIntArrayElements(env, jValueTypes, elements, 0);

    return valTypes;
}

bool checkException(JNIEnv *env, const char* msg) {
    if((*env)->ExceptionCheck(env)) {
        jthrowable err = (*env)->ExceptionOccurred(env);
        (*env)->ExceptionClear(env);

        jstring jErrorMsg = call_Object_toString(env, err);

        const char* cMsg = (*env)->GetStringUTFChars(env, jErrorMsg, NULL);
		fprintf(stderr, "%s: %s\n", msg, cMsg);
        (*env)->ReleaseStringUTFChars(env, jErrorMsg, cMsg);

        (*env)->DeleteLocalRef(env, jErrorMsg);
        (*env)->DeleteLocalRef(env, err);

        return true;
    }

    return false;
}

bool checkAndHandleException(JNIEnv *env, const char* msg) {
    if((*env)->ExceptionCheck(env)) {
        jthrowable err = (*env)->ExceptionOccurred(env);
        (*env)->ExceptionClear(env);

        jstring jErrorMsg = call_Object_toString(env, err);

        const char* cMsg = (*env)->GetStringUTFChars(env, jErrorMsg, NULL);
		fprintf(stderr, "%s: %s\n", msg, cMsg);
        (*env)->ReleaseStringUTFChars(env, jErrorMsg, cMsg);

        (*env)->ThrowNew(env, JC_RuntimeException, msg);

        (*env)->DeleteLocalRef(env, jErrorMsg);
        (*env)->DeleteLocalRef(env, err);

        return true;
    }
    return false;
}


void setJavaValueObject(JNIEnv *env, WasmEdge_Value value, jobject j_val) {
    switch (value.Type) {
        case WasmEdge_ValType_I32:
            setJavaIntValue(env, value, j_val);
            break;
        case WasmEdge_ValType_I64:
        case WasmEdge_ValType_FuncRef:
        case WasmEdge_ValType_V128:
            setJavaLongValue(env, value, j_val);
            break;
        case WasmEdge_ValType_F32:
            setJavaFloatValue(env, value, j_val);
            break;
        case WasmEdge_ValType_F64:
            setJavaDoubleValue(env, value, j_val);
            break;
        case WasmEdge_ValType_ExternRef:
            setExternRefStringVal(env, value, j_val);
            break;
        default:
            break;
    }
}

jstring WasmEdgeStringToJString(JNIEnv* env, WasmEdge_String wStr) {
    char buf[MAX_BUF_LEN];
    memset(buf, 0, MAX_BUF_LEN);
    WasmEdge_StringCopy(wStr, buf, MAX_BUF_LEN);

    jobject jStr = (*env)->NewStringUTF(env, buf);

    return jStr;
}

// Call 'free' on the returned string when no longer needed
char *JStringToCString(JNIEnv *env, jstring jstr) {
    const char *strPtr = (*env)->GetStringUTFChars(env, jstr, NULL);
    size_t len = (*env)->GetStringUTFLength(env, jstr);
    char *cStr = malloc(sizeof(char) * len);

    memcpy(cStr, strPtr, len);

    (*env)->ReleaseStringUTFChars(env, jstr, strPtr);

    return cStr;
}  


// Call 'WasmEdge_StringDelete' on the returned string when no longer needed
WasmEdge_String JStringToWasmString(JNIEnv* env, jstring jstr) {
    const char* strPtr = (*env)->GetStringUTFChars(env, jstr, NULL);

    WasmEdge_String wStr = WasmEdge_StringCreateByCString(strPtr);

    (*env)->ReleaseStringUTFChars(env, jstr, strPtr);

    return wStr;
}

// All strings in the array need releasing with ReleaseStringUTFCHars
const char** JStringArrayToPtrArray(JNIEnv* env, jarray jStrArray) {
    int len = (*env)->GetArrayLength(env, jStrArray);

    const char** ptr = malloc(sizeof(char*) * len);

    for(int i = 0; i < len; i++) {
        jstring  jStr = (*env)->GetObjectArrayElement(env, jStrArray, i);
        checkException(env, "Error getting array element");
        const char* strPtr = (*env)->GetStringUTFChars(env, jStr, NULL);
        ptr[i] = strPtr;
    }
    return ptr;
}

// Untested
void ReleasePtrArray(JNIEnv* env, jarray jStrArray, const char** ptr) {
    int len = (*env)->GetArrayLength(env, jStrArray);

    for(int i = 0; i < len; i++) {
        jstring jStr = (*env)->GetObjectArrayElement(env, jStrArray, i);
        checkException(env, "Error getting array element");
        (*env)->ReleaseStringUTFChars(env, jStr, ptr[i]);
    }

    free(ptr);
}

jobject WasmEdgeStringArrayToJavaList(JNIEnv* env, WasmEdge_String* wStrList, int32_t len) {
    jobject strList = construct_ArrayList(env, len);

    for (int i = 0; i < len; ++i) {
        jstring jstr = WasmEdgeStringToJString(env, wStrList[i]);
        call_List_add(env, strList, jstr);
        (*env)->DeleteLocalRef(env, jstr);
    }
    return strList;
}
