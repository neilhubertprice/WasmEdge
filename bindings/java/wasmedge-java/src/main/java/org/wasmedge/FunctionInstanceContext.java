package org.wasmedge;

public class FunctionInstanceContext extends AbstractWasmEdgeContext {
    public FunctionInstanceContext(final long pointer) {
        super(pointer);
    }

    public FunctionInstanceContext(final FunctionTypeContext type, final HostFunction hostFunction, final Object data,
                                   final long cost) {
        final String funcKey = WasmEdgeVM.addHostFunc(hostFunction);
        initialisePointer(nativeCreateFunction(type.getPointer(), funcKey, data, cost));
    }

    // Not currently implemented
//    public FunctionInstanceContext(FunctionTypeContext type, WrapFunction wrapFunction, Object binding,
//                                   Object data, long cost) {
//        this.pointer = nativeCreateBinding(type, wrapFunction, binding, data, cost);
//        validatePointer(pointer);
//    }

    private native long nativeCreateFunction(long funcTypePointer, String funcKey, Object data, long cost);

    // Not currently implemented
//    private native long nativeCreateBinding(long funcTypePointer, WrapFunction wrapFunction, Object binding,
//                                            Object data, long cost);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long funcInstancePointer);

    public FunctionTypeContext getFunctionType() {
        return new FunctionTypeContext(nativeGetFunctionType(pointer), null);
    }

    public native long nativeGetFunctionType(long funcInstancePointer);
}
