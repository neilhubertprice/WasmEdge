package org.wasmedge;

public class CompilerContext extends AbstractWasmEdgeContext {

    public CompilerContext(ConfigureContext configureContext) {
        initialisePointer(nativeInit(configureContext.getPointer()));
    }

    private native long nativeInit(long configureContextPointer);

    public void compile(String inputPath, String outputPath) {
        nativeCompile(pointer, inputPath, outputPath);
    }

    private native void nativeCompile(long compilerContextPointer, String inputPath, String outputPath);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long compilerContextPointer);
}
