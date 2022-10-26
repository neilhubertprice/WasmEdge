package org.wasmedge;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CopyOnWriteArrayList;

public class FunctionInstanceContext extends AbstractWasmEdgeContext {
    private static final List<HostFunction> hostFunctionList = new CopyOnWriteArrayList<>();
    private static final Map<HostFunction, Integer> hostFunctionMap = new HashMap<>();

    public FunctionInstanceContext(final long pointer) {
        super(pointer);
    }

    public FunctionInstanceContext(final FunctionTypeContext type, final HostFunction hostFunction, final long cost) {
        final int funcKey = FunctionInstanceContext.addHostFunction(hostFunction);
        initialisePointer(nativeCreateFunction(type.getPointer(), funcKey, cost));
    }

    private native long nativeCreateFunction(long funcTypePointer, long funcKey, long cost);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long funcInstancePointer);

    public FunctionTypeContext getFunctionType() {
        return new FunctionTypeContext(nativeGetFunctionType(pointer), null);
    }

    public native long nativeGetFunctionType(long funcInstancePointer);

    public static Result callHostFunction(long funcKey, long memoryInstancePointer, List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        final HostFunction hostFunction = FunctionInstanceContext.getHostFunction((int)funcKey);

        MemoryInstanceContext memoryInstanceContext = new MemoryInstanceContext(memoryInstancePointer);

        Result result = hostFunction.apply(memoryInstanceContext, params, returns);

        return result;
    }

    // Synchronized as we may have multiple threads registering host functions
    protected synchronized static int addHostFunction(HostFunction hostFunction) {
        if (hostFunctionMap.containsKey(hostFunction)) {
            return hostFunctionMap.get(hostFunction);
        }

        // We do not allow deletes, so list size is safe
        int newHFId = hostFunctionList.size();
        hostFunctionList.add(newHFId, hostFunction);

        return newHFId;
    }

    // Non-synchronized as we are using a CopyOnWriteArrayList
    protected static HostFunction getHostFunction(int hostFuncId) {
        return hostFunctionList.get(hostFuncId);
    }
}
