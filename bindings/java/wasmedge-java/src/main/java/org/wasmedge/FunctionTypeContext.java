package org.wasmedge;

import org.wasmedge.enums.ValueType;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class FunctionTypeContext {
    private long pointer;
    private String name;
    List<ValueType> parameters = null;
    List<ValueType> returns = null;

    public FunctionTypeContext(final long pointer, final String name) {
        this.pointer = pointer;
        validatePointer(pointer);
        this.name = name;
    }

    private void validatePointer(final long pointer) {
        if (pointer == 0) {
            throw new WasmEdgeException("Null FunctionType pointer");
        }
    }

    public FunctionTypeContext(final List<ValueType> paramTypes, final List<ValueType> returnTypes, final String name) {
        this.pointer = nativeInit(getTypeValues(paramTypes), getTypeValues(returnTypes));
        validatePointer(pointer);
        this.name = name;
        this.parameters = paramTypes;
        this.returns = returnTypes;
    }

    public FunctionTypeContext(final ValueType[] paramTypes, final ValueType[] returnTypes, final String name) {
        this(Arrays.asList(paramTypes), Arrays.asList(returnTypes), name);
    }

    private native long nativeInit(int[] paramsTypes, int[] returnTypes);

    private int[] getTypeValues(List<ValueType> valueTypeList) {
        int[] valueTypes = new int[valueTypeList.size()];
        IntStream.range(0, valueTypeList.size())
                .forEach(i -> valueTypes[i] = valueTypeList.get(i).getValue());
        return valueTypes;
    }

    private List<ValueType> getTypeList(int[] typeArray) {
        return IntStream.range(0, typeArray.length)
                .mapToObj(i -> ValueType.parseType(typeArray[i]))
                .collect(Collectors.toList());
    }

    public String getName() {
        return name;
    }

    public List<ValueType> getParameters() {
        if (parameters == null) {
            parameters = getTypeList(nativeGetParameters(pointer));
        }

        return parameters;
    }

    private native int[] nativeGetParameters(long funcTypePointer);

    public List<ValueType> getReturns() {
        if (returns == null) {
            returns = getTypeList(nativeGetReturns(pointer));
        }

        return returns;
    }

    private native int[] nativeGetReturns(long funcTypePointer);

    public void delete() {
        nativeDelete(pointer);
    }

    public native void nativeDelete(long funcTypePointer);

    private int[] getValueTypeArray(List<WasmEdgeValue> values) {

        int[] types = new int[values.size()];

        for (int i = 0; i < values.size(); i++) {
            types[i] = values.get(i).getType().ordinal();
        }
        return types;
    }

    private WasmEdgeValue[] valueListToArray(List<WasmEdgeValue> values) {
        WasmEdgeValue[] valuesArray = new WasmEdgeValue[values.size()];
        values.toArray(valuesArray);
        return valuesArray;
    }

    protected long getPointer() {
        return pointer;
    }
}
