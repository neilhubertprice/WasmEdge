package org.wasmedge;

import java.util.List;

public class ExecutorContext extends AbstractWasmEdgeContext {
    public ExecutorContext(ConfigureContext configureContext, StatisticsContext statisticsContext) {
        initialisePointer(nativeInit(configureContext.getPointer(), statisticsContext.getPointer()));
    }

    private native long nativeInit(long configureContextPointer, long statContextPointer);

    public void instantiate(StoreContext storeContext, ASTModuleContext astModuleContext) {
        nativeInstantiate(pointer, storeContext.getPointer(), astModuleContext.getPointer());
    }

    private native void nativeInstantiate(long executorContextPointer, long storeContextPointer, long astmContextPointer);

    public void invoke(StoreContext storeContext, String funcName,
                              List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        nativeInvoke(pointer, storeContext.getPointer(), funcName, params, returns);
    }

    private native void nativeInvoke(long executorContextPointer, long storeContextPointer, String funcName,
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
        nativeInvokeRegistered(pointer, storeContext.getPointer(), moduleName, funcName, params, returns);
    }

    private native void nativeInvokeRegistered(long executorContextPointer, long storeContextPointer, String moduleName,
                                               String funcName, List<WasmEdgeValue> params, List<WasmEdgeValue> returns);

    public void registerModule(StoreContext storeCxt, ASTModuleContext astCxt, String moduleName) {
        nativeRegisterModule(pointer, storeCxt.getPointer(), astCxt.getPointer(), moduleName);
    }

    private native void nativeRegisterModule(long executorContextPointer, long storeContextPointer, long astmContextPointer,
                                             String moduleName);

    public void registerImport(StoreContext storeCxt, ImportObjectContext importObjectContext) {
        nativeRegisterImport(pointer, storeCxt.getPointer(), importObjectContext);
    }

    private native void nativeRegisterImport(long executorContextPointer, long storeContextPointer, ImportObjectContext importObjectContext);

    @Override
    protected void doDelete() {
        nativeDelete(pointer);
    }

    private native void nativeDelete(long executorContextPointer);
}
