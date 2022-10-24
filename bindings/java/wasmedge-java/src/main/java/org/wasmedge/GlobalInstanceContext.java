package org.wasmedge;

public class GlobalInstanceContext extends AbstractWasmEdgeContext {
    private GlobalTypeContext globalTypeContext;
    private WasmEdgeValue value;

    protected GlobalInstanceContext(final long pointer) {
        super(pointer);
        // TODO This should probably be handled better as code below expects these values to be non-null
        globalTypeContext = null;
        value = null;
    }

    public GlobalInstanceContext(GlobalTypeContext typeCxt, WasmEdgeValue value) {
        this.globalTypeContext = typeCxt;
        this.value = value;
        initialisePointer(nativeInit(typeCxt.getPointer(), value));
    }

    private native long nativeInit(long globalTypePointer, WasmEdgeValue value);

    public GlobalTypeContext getGlobalType() {
        return globalTypeContext;
    }

    public WasmEdgeValue getValue() {
        return this.value;
    }

    public void setValue(WasmEdgeValue value) {
        this.value = value;
        nativeSetValue(pointer, value);
    }

    private native void nativeSetValue(long globalInstancePointer, WasmEdgeValue value);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    public native void nativeDelete(long globalInstancePointer);
}
