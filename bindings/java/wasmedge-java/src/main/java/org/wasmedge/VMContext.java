package org.wasmedge;

public class VMContext extends AbstractWasmEdgeContext {

    protected VMContext(long pointer) {
        super(pointer);
    }

    public VMContext(ConfigureContext configContext, StoreContext storeContext) {
        initNative(configContext.getPointer(), storeContext.getPointer());
    }

    private native long initNative(long configContextPointer, long storeContextPointer);

    public void cleanup() {
        nativeCleanup(pointer);
    }

    private native void nativeCleanup(long vmContextPointer);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long vmContextPointer);

}
