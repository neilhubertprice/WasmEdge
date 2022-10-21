package org.wasmedge;

public class StatisticsContext extends AbstractWasmEdgeContext {
    public StatisticsContext(final long pointer) {
        super(pointer);
    }

    public StatisticsContext() {
        initialisePointer(nativeInit());
    }

    private native long nativeInit();

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long statContextPointer);

    public int getInstrCount() {
        return nativeGetInstrCount(pointer);
    }

    private native int nativeGetInstrCount(long statContextPointer);

    public double getInstrPerSecond() {
        return nativeGetInstrPerSecond(pointer);
    }

    private native double nativeGetInstrPerSecond(long statContextPointer);

    public void setCostTable(long[] costTable) {
        nativeSetCostTable(pointer, costTable);
    }

    private native void nativeSetCostTable(long statContextPointer, long[] costTable);

    public void setCostLimit(long costLimit) {
        nativeSetCostLimit(pointer, costLimit);
    }

    private native void nativeSetCostLimit(long statContextPointer, long costLimit);

    public long getTotalCost() {
        return nativeGetTotalCost(pointer);
    }

    private native long nativeGetTotalCost(long statContextPointer);
}
