package org.wasmedge;

import java.util.ArrayList;
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
        long[] importTypePointers = nativeListImports(pointer);

        List<ImportTypeContext> importTypeContexts = new ArrayList<>(importTypePointers.length);
        for (int i = 0; i < importTypePointers.length; i++) {
            importTypeContexts.add(new ImportTypeContext(importTypePointers[i], this));
        }

        return importTypeContexts;
    }

    private native long[] nativeListImports(long astmContextPointer);

    public List<ExportTypeContext> listExports() {
        long[] exportTypePointers = nativeListExports(pointer);

        List<ExportTypeContext> exportTypeContexts = new ArrayList<>(exportTypePointers.length);
        for (int i = 0; i < exportTypePointers.length; i++) {
            exportTypeContexts.add(new ExportTypeContext(exportTypePointers[i], this));
        }

        return exportTypeContexts;
    }

    private native long[] nativeListExports(long astmContextPointer);
}
