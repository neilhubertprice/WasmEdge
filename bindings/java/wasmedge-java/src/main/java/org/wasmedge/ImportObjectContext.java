package org.wasmedge;

public class ImportObjectContext {
    private long pointer;

    public ImportObjectContext(String moduleName) {
        nativeInit(moduleName);
    }

    private ImportObjectContext(long pointer) {
        this.pointer = pointer;
    }

    public native static ImportObjectContext createWasmEdgeProcess(String[] allowedCmds, boolean allowAll);

    public native static ImportObjectContext CreateWASI(String[] args, String[] envs, String[] preopens);

    private native void nativeInit(String moduleName);

    public native void initWASI(String[] args, String[] envs, String[] preopens);

    public native int getWASIExitCode();

    public native void initWasmEdgeProcess(String[] allowedCmds, boolean allowAll);

    public void addFunction(String name, FunctionInstanceContext functionInstanceContext) {
        nativeAddFunction(name, functionInstanceContext.getPointer());
    }

    private native void nativeAddFunction(String name, long funcInstancePointer);

    public native void addTable(String name, TableInstanceContext tableInstanceContext);

    public native void addMemory(String name, MemoryInstanceContext memoryInstanceContext);

    public void addGlobal(String name, GlobalInstanceContext globalInstanceContext) {
        nativeAddGlobal(name, globalInstanceContext.getPointer());
    }

    private native void nativeAddGlobal(String name, long globalInstancePointer);

    public native void delete();
}
