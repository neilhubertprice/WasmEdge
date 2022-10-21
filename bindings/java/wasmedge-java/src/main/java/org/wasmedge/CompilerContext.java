package org.wasmedge;

public class CompilerContext {
    private long pointer;

    public CompilerContext(ConfigureContext configureContext) {
        nativeInit(configureContext.getPointer());
    }
    private native void nativeInit(long configureContextPointer);

    public native void compile(String inputPath, String outputPath);

    public native void delete();
}
