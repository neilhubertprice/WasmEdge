package org.wasmedge;

public class ValidatorContext extends AbstractWasmEdgeContext {

    public ValidatorContext(ConfigureContext configureContext) {
        initialisePointer(nativeInit(configureContext.getPointer()));
    }

    private native long nativeInit(long configureContextPointer);

    public void validate(ASTModuleContext astCtx) {
        nativeValidate(pointer, astCtx.getPointer());
    }

    private native void nativeValidate(long validatorContextPointer, long astmContextPointer);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long validatorContextPointer);
}
