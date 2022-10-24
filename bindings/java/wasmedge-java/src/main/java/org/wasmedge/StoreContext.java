package org.wasmedge;

import java.util.List;

public class StoreContext extends AbstractWasmEdgeContext {
    public StoreContext(final long pointer) {
        super(pointer);
    }

    public StoreContext() {
        initialisePointer(nativeInit());
    }

    private native long nativeInit();

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long storeContextPointer);


    public List<String> listFunction() {
        return nativeListFunction(pointer);
    }

    private native List<String> nativeListFunction(long storeContextPointer);

    public List<String> listFunctionRegistered(String moduleName) {
        return nativeListFunctionRegistered(pointer, moduleName);
    }

    private native List<String> nativeListFunctionRegistered(long storeContextPointer, String moduleName);

    public FunctionInstanceContext findFunction(String funcName) {
        return new FunctionInstanceContext(nativeFindFunction(pointer, funcName));
    }

    private native long nativeFindFunction(long storeContextPointer, String funcName);

    public FunctionInstanceContext findFunctionRegistered(String moduleName, String funcName) {
        return new FunctionInstanceContext(nativeFindFunctionRegistered(pointer, moduleName, funcName));
    }

    private native long nativeFindFunctionRegistered(long storeContextPointer, String moduleName, String funcName);

    public List<String> listTable() {
        return nativeListTable(pointer);
    }

    private native List<String> nativeListTable(long storeContextPointer);

    public List<String> listTableRegistered(String moduleName) {
        return nativeListTableRegistered(pointer, moduleName);
    }

    private native List<String> nativeListTableRegistered(long storeContextPointer, String moduleName);

    public TableInstanceContext findTable(String tableName) {
        return nativeFindTable(pointer, tableName);
    }

    private native TableInstanceContext nativeFindTable(long storeContextPointer, String tableName);

    public TableInstanceContext findTableRegistered(String moduleName, String tableName) {
        return nativeFindTableRegistered(pointer, moduleName, tableName);
    }

    private native TableInstanceContext nativeFindTableRegistered(long storeContextPointer, String moduleName, String tableName);

    public List<String> listMemory() {
        return nativeListMemory(pointer);
    }

    private native List<String> nativeListMemory(long storeContextPointer);

    public List<String> listMemoryRegistered(String moduleName) {
        return nativeListMemoryRegistered(pointer, moduleName);
    }

    private native List<String> nativeListMemoryRegistered(long storeContextPointer, String moduleName);

    public MemoryInstanceContext findMemory(String memoryName) {
        return new MemoryInstanceContext(nativeFindMemory(pointer, memoryName));
    }

    private native long nativeFindMemory(long storeContextPointer, String memoryName);

    public MemoryInstanceContext findMemoryRegistered(String moduleName, String memoryName) {
        return new MemoryInstanceContext(nativeFindMemoryRegistered(pointer, moduleName, memoryName));
    }

    private native long nativeFindMemoryRegistered(long storeContextPointer, String moduleName, String memoryName);

    public List<String> listGlobal() {
        return nativeListGlobal(pointer);
    }

    private native List<String> nativeListGlobal(long storeContextPointer);

    public List<String> listGlobalRegistered(String moduleName) {
        return nativeListGlobalRegistered(pointer, moduleName);
    }

    private native List<String> nativeListGlobalRegistered(long storeContextPointer, String moduleName);

    public GlobalInstanceContext findGlobal(String name) {
        return new GlobalInstanceContext(nativeFindGlobal(pointer, name));
    }

    private native long nativeFindGlobal(long storeContextPointer, String name);

    public GlobalInstanceContext findGlobalRegistered(String moduleName, String globalName) {
        return new GlobalInstanceContext(nativeFindGlobalRegistered(pointer, moduleName, globalName));
    }

    private native long nativeFindGlobalRegistered(long storeContextPointer, String moduleName, String globalName);

    public List<String> listModule() {
        return nativeListModule(pointer);
    }

    private native List<String> nativeListModule(long storeContextPointer);

}
