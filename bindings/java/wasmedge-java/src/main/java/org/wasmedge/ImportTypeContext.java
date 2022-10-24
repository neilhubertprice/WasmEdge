package org.wasmedge;

import org.wasmedge.enums.ExternalType;

public class ImportTypeContext {
    private final ASTModuleContext astCtx;

    private final long pointer;

    private ImportTypeContext(long pointer, ASTModuleContext astCtx) {
        this.pointer = pointer;
        this.astCtx = astCtx;
    }

    public native String getModuleName();

    public native String getExternalName();

    public ExternalType getExternalType() {
        return ExternalType.getByValue(nativeGetExternalType());
    }

    private native int nativeGetExternalType();

    public FunctionTypeContext getFunctionType() {
        return new FunctionTypeContext(nativeGetFunctionType(astCtx.getPointer()), null);
    }

    private native long nativeGetFunctionType(long astmContextPointer);

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

}
