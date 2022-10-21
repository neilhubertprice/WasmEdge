package org.wasmedge;

public class VMContext {
    private long pointer;

    public VMContext(ConfigureContext configContext, StoreContext storeContext) {
        initNative(configContext.getPointer(), storeContext);
    }

    public void release() {
        this.cleanUp();
        pointer = 0;
    }

    private native void initNative(long configContextPointer, StoreContext storeContext);

    private native void cleanUp();

}
