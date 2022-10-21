package org.wasmedge;

public class LoaderContext {
    private long pointer;

    public LoaderContext(ConfigureContext configureContext) {
        nativeInit(configureContext.getPointer());
    }

    private native void nativeInit(long configureContextPointer);

    public ASTModuleContext parseFromFile(String path) {
        return new ASTModuleContext(nativeParseFromFile(path));
    }

    private native long nativeParseFromFile(String path);

    public ASTModuleContext parseFromBuffer(byte[] buf, int bufSize) {
        return new ASTModuleContext(nativeParseFromBuffer(buf, bufSize));
    }

    private native long nativeParseFromBuffer(byte[] buf, int bufSize);

    public native void delete();
}
