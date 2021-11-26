package org.wasmedge;

public class ConfigureContext {
    private long pointer;

    public ConfigureContext() {
        nativeInit();
    }

    private native void nativeInit();
    private native void delete();
    public native void addHostRegistration();

    public native void setMaxMemoryPage(long pages);

    public native void setStatisticsSetInstructionCounting(boolean statisticsSetInstructionCounting);

    public native void setStatisticsSetCostMeasuring(boolean statisticsSetCostMeasuring);

    public native void setStatisticsSetTimeMeasuring(boolean statisticsSetTimeMeasuring);

    public void destroy() {
        delete();
        pointer = 0;
    }

}
