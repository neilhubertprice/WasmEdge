package org.wasmedge;

import org.wasmedge.enums.CompilerOptimizationLevel;
import org.wasmedge.enums.CompilerOutputFormat;
import org.wasmedge.enums.HostRegistration;
import org.wasmedge.enums.Proposal;

public class ConfigureContext extends AbstractWasmEdgeContext {
    public ConfigureContext(final long pointer) {
        super(pointer);
    }

    public ConfigureContext() {
        initialisePointer(nativeInit());
    }

    private native long nativeInit();

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long configContextPointer);

    public void addProposal(Proposal proposal) {
        nativeAddProposal(pointer, proposal.ordinal());
    }

    private native void nativeAddProposal(long configContextPointer, int proposal);

    public void removeProposal(Proposal proposal) {
        nativeRemoveProposal(pointer, proposal.ordinal());
    }

    private native void nativeRemoveProposal(long configContextPointer, int proposal);

    public boolean hasProposal(Proposal proposal) {
        return nativeHasProposal(pointer, proposal.ordinal());
    }

    private native boolean nativeHasProposal(long configContextPointer, int proposal);

    public void addHostRegistration(HostRegistration hostRegistration) {
        nativeAddHostRegistration(pointer, hostRegistration.ordinal());
    }

    private native void nativeAddHostRegistration(long configContextPointer, int hostRegistration);

    public void removeHostRegistration(HostRegistration hostRegistration) {
        nativeRemoveHostRegistration(pointer, hostRegistration.ordinal());
    }

    private native void nativeRemoveHostRegistration(long configContextPointer, int hostRegistration);

    public boolean hasHostRegistration(HostRegistration hostRegistration) {
        return nativeHasHostRegistration(pointer, hostRegistration.ordinal());
    }

    private native boolean nativeHasHostRegistration(long configContextPointer, int hostRegistration);

    public long getMaxMemoryPage() {
        return nativeGetMaxMemoryPage(pointer);
    }

    private native long nativeGetMaxMemoryPage(long configContextPointer);

    public void setMaxMemoryPage(long pages) {
        nativeSetMaxMemoryPage(pointer, pages);
    }

    private native void nativeSetMaxMemoryPage(long configContextPointer, long pages);

    public CompilerOptimizationLevel getCompilerOptimizationLevel() {
        return CompilerOptimizationLevel.values()[nativeGetCompilerOptimizationLevel(pointer)];
    }

    private native int nativeGetCompilerOptimizationLevel(long configContextPointer);

    public void setCompilerOptimizationLevel(CompilerOptimizationLevel optimizationLevel) {
        nativeSetCompilerOptimizationLevel(pointer, optimizationLevel.ordinal());
    }

    private native void nativeSetCompilerOptimizationLevel(long configContextPointer, int optimizationLevel);

    public CompilerOutputFormat getCompilerOutputFormat() {
        return CompilerOutputFormat.values()[nativeGetCompilerOutputFormat(pointer)];
    }

    private native int nativeGetCompilerOutputFormat(long configContextPointer);

    public void setCompilerOutputFormat(CompilerOutputFormat compilerOutputFormat) {
        nativeSetCompilerOutputFormat(pointer, compilerOutputFormat.ordinal());
    }

    private native void nativeSetCompilerOutputFormat(long configContextPointer, int compilerOutputFormat);

    public boolean getCompilerIsDumpIR() {
        return nativeGetCompilerIsDumpIR(pointer);
    }

    private native boolean nativeGetCompilerIsDumpIR(long configContextPointer);

    public void setCompilerIsDumpIR(boolean isDumpIR) {
        nativeSetCompilerIsDumpIR(pointer, isDumpIR);
    }

    private native void nativeSetCompilerIsDumpIR(long configContextPointer, boolean isDumpIR);

    public boolean getCompilerIsGenericBinary() {
        return nativeGetCompilerIsGenericBinary(pointer);
    }

    private native boolean nativeGetCompilerIsGenericBinary(long configContextPointer);

    public void setCompilerIsGenericBinary(boolean isGenericBinary) {
        nativeSetCompilerIsGenericBinary(pointer, isGenericBinary);
    }

    private native void nativeSetCompilerIsGenericBinary(long configContextPointer, boolean isGenericBinary);

    public boolean isStatisticsSetInstructionCounting() {
        return nativeIsStatisticsSetInstructionCounting(pointer);
    }

    private native boolean nativeIsStatisticsSetInstructionCounting(long configContextPointer);

    public void setStatisticsSetInstructionCounting(boolean statisticsSetInstructionCounting) {
        nativeSetStatisticsSetInstructionCounting(pointer, statisticsSetInstructionCounting);
    }

    private native void nativeSetStatisticsSetInstructionCounting(long configContextPointer, boolean statisticsSetInstructionCounting);

    public boolean isStatisticsSetCostMeasuring() {
        return nativeIsStatisticsSetCostMeasuring(pointer);
    }

    private native boolean nativeIsStatisticsSetCostMeasuring(long configContextPointer);

    public void setStatisticsSetCostMeasuring(boolean statisticsSetCostMeasuring) {
        nativeSetStatisticsSetCostMeasuring(pointer, statisticsSetCostMeasuring);
    }

    private native void nativeSetStatisticsSetCostMeasuring(long configContextPointer, boolean statisticsSetCostMeasuring);

    public boolean isStatisticsSetTimeMeasuring() {
        return nativeIsStatisticsSetTimeMeasuring(pointer);
    }

    private native boolean nativeIsStatisticsSetTimeMeasuring(long configContextPointer);

    public void setStatisticsSetTimeMeasuring(boolean statisticsSetTimeMeasuring) {
        nativeSetStatisticsSetTimeMeasuring(pointer, statisticsSetTimeMeasuring);
    }

    private native void nativeSetStatisticsSetTimeMeasuring(long configContextPointer, boolean statisticsSetTimeMeasuring);

}
