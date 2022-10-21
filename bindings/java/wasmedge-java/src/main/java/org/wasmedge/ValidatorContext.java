package org.wasmedge;

public class ValidatorContext {
    private long pointer;

    public ValidatorContext(ConfigureContext configureContext) {
        nativeInit(configureContext.getPointer());
    }

    public void validate(ASTModuleContext astCtx) {
        nativeValidate(astCtx.getPointer());
    }

    private native void nativeValidate(long astmContextPointer);

    private native void nativeInit(long configureContextPointer);

    public native void delete();
}
