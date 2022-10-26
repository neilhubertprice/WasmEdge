package org.wasmedge;

import org.wasmedge.enums.ValueType;

import java.util.UUID;

public class WasmEdgeExternRef<T> implements WasmEdgeValue {
    private String value;

    protected WasmEdgeExternRef() {
        this.value = null;
    }

    protected WasmEdgeExternRef(String strVal) {
        this.value = strVal;
    }

    public WasmEdgeExternRef(T val) {
        final String key = UUID.randomUUID().toString();
        this.value = key;
        WasmEdgeVM.addExternRef(key, val);
    }

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
