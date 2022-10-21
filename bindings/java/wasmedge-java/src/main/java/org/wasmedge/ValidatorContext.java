package org.wasmedge;

public class ValidatorContext {
    private long pointer;

    public ValidatorContext(ConfigureContext configureContext) {
        nativeInit(configureContext.getPointer());
    }

    public native void validate(ASTModuleContext astCtx);

    private native void nativeInit(long configureContextPointer);

    public native void delete();
}
