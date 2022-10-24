package org.wasmedge;

import org.wasmedge.enums.ValueType;

import java.util.UUID;

public class WasmEdgeExternRef<T> implements WasmEdgeValue {
    private long pointer;
    private String value;

    public WasmEdgeExternRef(T val) {
        final String key = UUID.randomUUID().toString();
        this.value = key;
        WasmEdgeVM.addExternRef(key, val);
        initialisePointer(nativeInit(key));
    }

    protected void initialisePointer(long pointer) {
        this.pointer = pointer;
        validatePointer(pointer);
    }

    private void validatePointer(final long pointer) {
        if (pointer == 0) {
            throw new WasmEdgeException("Null WasmEdgeExternRef pointer");
        }
    }

    private native long nativeInit(String key);

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public T getExtValue() {
        return (T) WasmEdgeVM.getExternRef(value);
    }

    @Override
    public ValueType getType() {
        return ValueType.ExternRef;
    }

}
