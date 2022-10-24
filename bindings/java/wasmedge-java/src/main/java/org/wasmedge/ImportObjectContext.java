package org.wasmedge;

public class ImportObjectContext extends AbstractWasmEdgeContext {

    protected ImportObjectContext(long pointer) {
        super(pointer);
    }

    public ImportObjectContext(String moduleName) {
        initialisePointer(nativeInit(moduleName));
    }

    private native long nativeInit(String moduleName);

    public static ImportObjectContext createWasmEdgeProcess(String[] allowedCmds, boolean allowAll) {
        return new ImportObjectContext(nativeCreateWasmEdgeProcess(allowedCmds, allowAll));
    }

    private native static long nativeCreateWasmEdgeProcess(String[] allowedCmds, boolean allowAll);

    public static ImportObjectContext CreateWASI(String[] args, String[] envs, String[] preopens) {
        return new ImportObjectContext(nativeCreateWASI(args, envs, preopens));
    }

    private native static long nativeCreateWASI(String[] args, String[] envs, String[] preopens);

    public void initWASI(String[] args, String[] envs, String[] preopens) {
        nativeInitWASI(pointer, args, envs, preopens);
    }

    private native void nativeInitWASI(long importObjectPointer, String[] args, String[] envs, String[] preopens);

    public int getWASIExitCode() {
        return nativeGetWASIExitCode(pointer);
    }

    private native int nativeGetWASIExitCode(long importObjectPointer);

    public void initWasmEdgeProcess(String[] allowedCmds, boolean allowAll) {
        nativeInitWasmEdgeProcess(pointer, allowedCmds, allowAll);
    }

    private native void nativeInitWasmEdgeProcess(long importObjectPointer, String[] allowedCmds, boolean allowAll);

    public void addFunction(String name, FunctionInstanceContext functionInstanceContext) {
        nativeAddFunction(pointer, name, functionInstanceContext.getPointer());
    }

    private native void nativeAddFunction(long importObjectPointer, String name, long funcInstancePointer);

    public void addTable(String name, TableInstanceContext tableInstanceContext) {
        nativeAddTable(pointer, name, tableInstanceContext);
    }

    private native void nativeAddTable(long importObjectPointer, String name, TableInstanceContext tableInstanceContext);

    public void addMemory(String name, MemoryInstanceContext memoryInstanceContext) {
        nativeAddMemory(pointer, name, memoryInstanceContext);
    }

    private native void nativeAddMemory(long importObjectPointer, String name, MemoryInstanceContext memoryInstanceContext);

    public void addGlobal(String name, GlobalInstanceContext globalInstanceContext) {
        nativeAddGlobal(pointer, name, globalInstanceContext.getPointer());
    }

    private native void nativeAddGlobal(long importObjectPointer, String name, long globalInstancePointer);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long importObjectPointer);
}
