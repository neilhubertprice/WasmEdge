package org.wasmedge;

public class LoaderContext {
    private long pointer;

    public LoaderContext(ConfigureContext configureContext) {
        nativeInit(configureContext.getPointer());
    }

    private native void nativeInit(long configureContextPointer);

    public native ASTModuleContext parseFromFile(String path);

    public native ASTModuleContext parseFromBuffer(byte[] buf, int bufSize);

    public native void delete();
}
