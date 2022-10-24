package org.wasmedge;

import org.wasmedge.enums.ValueType;

public class TableInstanceContext extends AbstractWasmEdgeContext {
    private TableTypeContext tableTypeContext;

    protected TableInstanceContext(long pointer) {
        super(pointer);
    }

    public TableInstanceContext(TableTypeContext tableTypeContext) {
        this.tableTypeContext = tableTypeContext;
        initialisePointer(nativeInit(tableTypeContext.getPointer()));
    }

    private native long nativeInit(long tableTypePointer);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long tableInstancePointer);

    public TableTypeContext getTableType() {
        return this.tableTypeContext;
    }

    public void setData(WasmEdgeValue value, int index) {
        nativeSetData(pointer, value, index);
    }

    private native void nativeSetData(long tableInstancePointer, WasmEdgeValue value, int index);

    public WasmEdgeValue getData(ValueType valueType, int offSet) {
        return nativeGetData(pointer, valueType, offSet);
    }

    private native WasmEdgeValue nativeGetData(long tableInstancePointer, ValueType valueType, int offSet);

    public int getSize() {
        return getSize(pointer);
    }

    private native int getSize(long tableInstancePointer);

    public void grow(int size) {
        nativeGrow(pointer, size);
    }

    private native void nativeGrow(long tableInstancePointer, int size);

}
