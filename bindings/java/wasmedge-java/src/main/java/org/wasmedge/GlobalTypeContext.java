package org.wasmedge;

import org.wasmedge.enums.ValueType;
import org.wasmedge.enums.WasmEdgeMutability;

public class GlobalTypeContext extends AbstractWasmEdgeContext {

    protected GlobalTypeContext(long pointer) {
        super(pointer);
    }

    public GlobalTypeContext(ValueType valueType, WasmEdgeMutability wasmEdgeMutability) {
        initialisePointer(nativeInit(valueType.getValue(), wasmEdgeMutability.getValue()));
    }

    private native long nativeInit(int valueType, int wasmEdgeMutability);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long globalTypePointer);

    public ValueType getValueType() {
        return ValueType.parseType(nativeGetValueType(pointer));
    }

    private native int nativeGetValueType(long globalTypePointer);

    public WasmEdgeMutability getMutability() {
        return WasmEdgeMutability.parseMutability(nativeGetMutability(pointer));
    }

    private native int nativeGetMutability(long globalTypePointer);
}
