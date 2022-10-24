package org.wasmedge;

import org.wasmedge.enums.ExternalType;

public class ExportTypeContext extends AbstractWasmEdgeContext {
    private final ASTModuleContext astCtx;

    protected ExportTypeContext(long pointer, ASTModuleContext astCtx) {
        this.pointer = pointer;
        this.astCtx = astCtx;
    }

    public String getExternalName() {
        return getExternalName(pointer);
    }

    private native String getExternalName(long exportTypePointer);

    public ExternalType getExternalType() {
        return ExternalType.getByValue(nativeGetExternalType(pointer));
    }

    private native int nativeGetExternalType(long exportTypePointer);


    public FunctionTypeContext getFunctionType() {
        return new FunctionTypeContext(nativeGetFunctionType(pointer, astCtx.getPointer()), null);
    }

    private native long nativeGetFunctionType(long exportTypePointer, long astmContextPointer);

    public TableTypeContext getTableType() {
        return nativeGetTableType(astCtx.getPointer());
    }

    private native TableTypeContext nativeGetTableType(long astmContextPointer);

    public MemoryTypeContext getMemoryType() {
        return nativeGetMemoryType(astCtx.getPointer());
    }

    private native MemoryTypeContext nativeGetMemoryType(long astmContextPointer);

    public GlobalTypeContext getGlobalType() {
        return new GlobalTypeContext(nativeGetGlobalType(astCtx.getPointer()));
    }

    private native long nativeGetGlobalType(long astmContextPointer);

    @Override
    protected void doDelete() {
        throw new WasmEdgeException("Delete operation not supported on ExportTypeContext");
    }
}
