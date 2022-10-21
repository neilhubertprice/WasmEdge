package org.wasmedge;

import java.util.List;

public class ASTModuleContext extends AbstractWasmEdgeContext {
    public ASTModuleContext(final long pointer) {
        super(pointer);
    }

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long astmContextPointer);

    public List<ImportTypeContext> listImports() {
        return nativeListImports(pointer);
    }

    private native List<ImportTypeContext> nativeListImports(long astmContextPointer);

    public List<ExportTypeContext> listExports() {
        return nativeListExports(pointer);
    }

    private native List<ExportTypeContext> nativeListExports(long astmContextPointer);
}
