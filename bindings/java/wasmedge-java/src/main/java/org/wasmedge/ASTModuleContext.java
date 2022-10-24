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
        return nativeListImports(pointer);
    }

    private native List<ImportTypeContext> nativeListImports(long astmContextPointer);

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
