package org.wasmedge;

import java.util.List;

public class StoreContext {
    private long pointer = 0;

    public StoreContext() {
        nativeInit();
    }

    private StoreContext(long pointer) {
        this.pointer = pointer;
    }

    public void destroy() {
        delete();
        pointer = 0;
    }

    private native void nativeInit();

    private native void delete();


    public native List<String> listFunction();

    public native List<String> listFunctionRegistered(String moduleName);

    public FunctionInstanceContext findFunction(String funcName) {
        return new FunctionInstanceContext(nativeFindFunction(funcName));
    }

    private native long nativeFindFunction(String funcName);

    public FunctionInstanceContext findFunctionRegistered(String moduleName, String funcName) {
        return new FunctionInstanceContext(nativeFindFunctionRegistered(moduleName, funcName));
    }

    private native long nativeFindFunctionRegistered(String moduleName, String funcName);

    public native List<String> listTable();

    public native List<String> listTableRegistered(String moduleName);

    public native TableInstanceContext findTable(String tableName);

    public native TableInstanceContext findTableRegistered(String moduleName, String tableName);

    public native List<String> listMemory();

    public native List<String> listMemoryRegistered(String moduleName);

    public native MemoryInstanceContext findMemory(String memoryName);

    public native MemoryInstanceContext findMemoryRegistered(String moduleName,
                                                             String memoryName);

    public native List<String> listGlobal();

    public native List<String> listGlobalRegistered(String moduleName);

    public native GlobalInstanceContext findGlobal(String name);

    public native GlobalInstanceContext findGlobalRegistered(String moduleName,
                                                             String globalName);

    public native List<String> listModule();

}
