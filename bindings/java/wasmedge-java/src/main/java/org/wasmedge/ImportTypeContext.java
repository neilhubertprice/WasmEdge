package org.wasmedge;

import org.wasmedge.enums.ExternalType;

public class ImportTypeContext extends AbstractWasmEdgeContext {
    private final ASTModuleContext astCtx;

    protected ImportTypeContext(long pointer, ASTModuleContext astCtx) {
        super(pointer);
        this.astCtx = astCtx;
    }

    public String getModuleName() {
        return nativeGetModuleName(pointer);
    }

    private native String nativeGetModuleName(long importTypePointer);

    public String getExternalName() {
        return nativeGetExternalName(pointer);
    }

    private native String nativeGetExternalName(long importTypePointer);

    public ExternalType getExternalType() {
        return ExternalType.getByValue(nativeGetExternalType(pointer));
    }

    private native int nativeGetExternalType(long importTypePointer);

    public FunctionTypeContext getFunctionType() {
        return new FunctionTypeContext(nativeGetFunctionType(pointer, astCtx.getPointer()), null);
    }

    private native long nativeGetFunctionType(long importTypePointer, long astmContextPointer);

    public TableTypeContext getTableType() {
        return nativeGetTableType(pointer, astCtx.getPointer());
    }

    private native TableTypeContext nativeGetTableType(long importTypePointer, long astmContextPointer);

    public MemoryTypeContext getMemoryType() {
        return new MemoryTypeContext(nativeGetMemoryType(pointer, astCtx.getPointer()));
    }

    private native long nativeGetMemoryType(long importTypePointer, long astmContextPointer);

    public GlobalTypeContext getGlobalType() {
        return new GlobalTypeContext(nativeGetGlobalType(pointer, astCtx.getPointer()));
    }

    private native long nativeGetGlobalType(long importTypePointer, long astmContextPointer);

    @Override
    protected void doDelete() {
        throw new WasmEdgeException("Delete operation not supported on ImportTypeContext");
    }
}
