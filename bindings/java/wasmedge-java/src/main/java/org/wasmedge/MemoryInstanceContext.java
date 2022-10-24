package org.wasmedge;

public class MemoryInstanceContext extends AbstractWasmEdgeContext {
    private MemoryTypeContext memoryTypeContext;

    protected MemoryInstanceContext(long pointer) {
        super(pointer);
    }

    public MemoryInstanceContext(MemoryTypeContext memoryTypeContext) {
        this.memoryTypeContext = memoryTypeContext;
        initialisePointer(nativeInit(memoryTypeContext.getPointer()));
    }

    private native long nativeInit(long memoryTypePointer);

    public void setData(byte[] data, int offSet, int length) {
        nativeSetData(pointer, data, offSet, length);
    }

    private native void nativeSetData(long memoryInstancePointer, byte[] data, int offSet, int length);

    public byte[] getData(int offSet, int length) {
        return nativeGetData(pointer, offSet, length);
    }

    private native byte[] nativeGetData(long memoryInstancePointer, int offSet, int length);

    public int getPageSize() {
        return nativeGetPageSize(pointer);
    }

    private native int nativeGetPageSize(long memoryInstancePointer);

    public void growPage(int size) {
        nativeGrowPage(pointer, size);
    }

    private native void nativeGrowPage(long memoryInstancePointer, int size);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long memoryInstancePointer);
}
