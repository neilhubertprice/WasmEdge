package org.wasmedge;

public class MemoryTypeContext extends AbstractWasmEdgeContext {
    private WasmEdgeLimit limit;

    protected MemoryTypeContext(long pointer) {
        super(pointer);
    }

    public MemoryTypeContext(WasmEdgeLimit limit) {
        this.limit = limit;
        initialisePointer(nativeInit(limit.isHasMax(), limit.getMin(), limit.getMax()));
    }

    private native long nativeInit(boolean hasMax, long min, long max);

    public WasmEdgeLimit getLimit() {
        if (limit == null) {
            limit = nativeGetLimit(pointer);
        }

        return limit;
    }

    private native WasmEdgeLimit nativeGetLimit(long memoryTypePointer);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long memoryTypePointer);
}
