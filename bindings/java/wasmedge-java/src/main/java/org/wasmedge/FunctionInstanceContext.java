package org.wasmedge;

public class FunctionInstanceContext {
    private long pointer;

    public FunctionInstanceContext(final long pointer) {
        this.pointer = pointer;
        validatePointer(pointer);
    }

    private void validatePointer(final long pointer) {
        if (pointer == 0) {
            throw new WasmEdgeException("Null FunctionInstance pointer");
        }
    }

    public FunctionInstanceContext(final FunctionTypeContext type, final HostFunction hostFunction, final Object data,
                                   final long cost) {
        final String funcKey = WasmEdgeVM.addHostFunc(hostFunction);
        this.pointer = nativeCreateFunction(type.getPointer(), funcKey, data, cost);
        validatePointer(pointer);
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

    public void delete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long funcInstancePointer);

    public FunctionTypeContext getFunctionType() {
        return new FunctionTypeContext(nativeGetFunctionType(pointer), null);
    }

    public native long nativeGetFunctionType(long funcInstancePointer);

    protected long getPointer() {
        return pointer;
    }
}
