package org.wasmedge;

public class LoaderContext extends AbstractWasmEdgeContext {

    public LoaderContext(ConfigureContext configureContext) {
        initialisePointer(nativeInit(configureContext.getPointer()));
    }

    private native long nativeInit(long configureContextPointer);

    public ASTModuleContext parseFromFile(String path) {
        return new ASTModuleContext(nativeParseFromFile(pointer, path));
    }

    private native long nativeParseFromFile(long loaderContextPointer, String path);

    public ASTModuleContext parseFromBuffer(byte[] buf, int bufSize) {
        return new ASTModuleContext(nativeParseFromBuffer(pointer, buf, bufSize));
    }

    private native long nativeParseFromBuffer(long loaderContextPointer, byte[] buf, int bufSize);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long loaderContextPointer);
}
