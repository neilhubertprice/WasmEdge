package org.wasmedge;

import java.util.List;

public class ExecutorContext {
    private long pointer;

    public ExecutorContext(ConfigureContext configureContext, StatisticsContext statisticsContext) {
        nativeInit(configureContext.getPointer(), statisticsContext.getPointer());
    }

    private native void nativeInit(long configureContextPointer, long statContextPointer);

    public void instantiate(StoreContext storeContext, ASTModuleContext astModuleContext) {
        nativeInstantiate(storeContext.getPointer(), astModuleContext.getPointer());
    }

    private native void nativeInstantiate(long storeContextPointer, long astmContextPointer);

    public void invoke(StoreContext storeContext, String funcName,
                              List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        nativeInvoke(storeContext.getPointer(), funcName, params, returns);
    }

    private native void nativeInvoke(long storeContextPointer, String funcName,
                              List<WasmEdgeValue> params, List<WasmEdgeValue> returns);


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

    public void invokeRegistered(StoreContext storeContext, String moduleName, String funcName,
                                        List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        nativeInvokeRegistered(storeContext.getPointer(), moduleName, funcName, params, returns);
    }

    private native void nativeInvokeRegistered(long storeContextPointer, String moduleName, String funcName,
                                        List<WasmEdgeValue> params, List<WasmEdgeValue> returns);

    public void registerModule(StoreContext storeCxt, ASTModuleContext astCxt, String moduleName) {
        nativeRegisterModule(storeCxt.getPointer(), astCxt.getPointer(), moduleName);
    }

    private native void nativeRegisterModule(long storeContextPointer, long astmContextPointer, String moduleName);

    public void registerImport(StoreContext storeCxt, ImportObjectContext importObjectContext) {
        nativeRegisterImport(storeCxt.getPointer(), importObjectContext);
    }

    private native void nativeRegisterImport(long storeContextPointer, ImportObjectContext importObjectContext);

    public native void delete();
}
