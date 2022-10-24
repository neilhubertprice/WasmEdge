package org.wasmedge;

import org.wasmedge.enums.RefType;

public class TableTypeContext extends AbstractWasmEdgeContext {

    protected TableTypeContext(long pointer) {
        super(pointer);
    }

    public TableTypeContext(RefType refType, WasmEdgeLimit limit) {
        initialisePointer(nativeInit(refType.getVal(), limit.isHasMax(), limit.getMin(), limit.getMax()));
    }

    private native long nativeInit(int refType, boolean hasMax, long min, long max);

    public WasmEdgeLimit getLimit() {
        return nativeGetLimit(pointer);
    }

    private native WasmEdgeLimit nativeGetLimit(long tableTypePointer);

    public RefType getRefType() {
        return RefType.getType(nativeGetRefType(pointer));
    }

    private native int nativeGetRefType(long tableTypePointer);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long tableTypePointer);
}
