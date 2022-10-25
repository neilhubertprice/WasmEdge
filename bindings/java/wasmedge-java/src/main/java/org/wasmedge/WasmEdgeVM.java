package org.wasmedge;

import org.wasmedge.enums.HostRegistration;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.UUID;

public class WasmEdgeVM {
    private static final Map<String, Object> externRefMap = new HashMap<>();
    private final ConfigureContext configureContext;
    private final StoreContext storeContext;
    private VMContext vmContext;


    public WasmEdgeVM(ConfigureContext configureContext, StoreContext storeContext) {
        this.configureContext = configureContext;
        this.storeContext = storeContext;
        this.vmContext = new VMContext(nativeInit(configureContext.getPointer(), storeContext.getPointer()));
    }

    private native long nativeInit(long configureContextPointer, long storeContextPointer);

    protected static void addExternRef(String key, Object val) {
        externRefMap.put(key, val);
    }

    protected static Object getExternRef(String key) {
        return externRefMap.get(key);
    }

    /**
     * Run a wasm file.
     *
     * @param file     file path.
     * @param funcName function name to run.
     * @param params   params for the function.
     * @param returns  return values.
     */
    public void runWasmFromFile(String file, String funcName, List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);

        nativeRunWasmFromFile(vmContext.getPointer(), file, funcName, paramsArray, params.size(), paramTypes,
                returnsArray, returns.size(), returnTypes);
    }

    private native void nativeRunWasmFromFile(long vmContextPointer, String file, String funcName, WasmEdgeValue[] params, int paramSize, int[] paramTypes,
                                              WasmEdgeValue[] returns, int returnSize, int[] returnTypes);

    public void runWasmFromBuffer(byte[] buffer, String funcName, List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);

        nativeRunWasmFromBuffer(vmContext.getPointer(), buffer, funcName, paramsArray, paramTypes, returnsArray, returnTypes);
    }

    private native void nativeRunWasmFromBuffer(long vmContextPointer, byte[] buffer, String funcName, WasmEdgeValue[] params,
                                                int[] paramTypes, WasmEdgeValue[] returns, int[] returnTypes);

    public void runWasmFromASTModule(ASTModuleContext astModuleContext, String funcName, List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);

        nativeRunWasmFromASTModule(vmContext.getPointer(), astModuleContext.getPointer(), funcName, paramsArray, paramTypes,
                returnsArray, returnTypes);
    }

    private native void nativeRunWasmFromASTModule(long vmContextPointer, long astmContextPointer, String funcName, WasmEdgeValue[] params,
                                                   int[] paramTypes, WasmEdgeValue[] returns, int[] returnTypes);

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

    public void loadWasmFromFile(String filePath) {
        nativeLoadWasmFromFile(vmContext.getPointer(), filePath);
    }

    private native void nativeLoadWasmFromFile(long vmContextPointer, String filePath);

    // Not yet implemented in the JNI layer
//    public native void loadWasmFromBuffer(byte[] buffer);
//
//    public native void loadWasmFromASTModule(ASTModuleContext astModuleContext);

    public void validate() {
        nativeValidate(vmContext.getPointer());
    }

    private native void nativeValidate(long vmContextPointer);

    public void instantiate() {
        nativeInstantiate(vmContext.getPointer());
    }

    private native void nativeInstantiate(long vmContextPointer);

    public void execute(String funcName, List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);

        nativeExecute(vmContext.getPointer(), funcName, paramsArray, params.size(), paramTypes,
                returnsArray, returns.size(), returnTypes);
    }

    private native void nativeExecute(long vmContextPointer, String funcName, WasmEdgeValue[] params, int paramSize,
                                      int[] paramTypes, WasmEdgeValue[] returns, int returnSize, int[] returnTypes);

    // Also cleans up ConfigureContext & StoreContext
    public void destroy() {
        if (configureContext != null) {
            configureContext.delete();
        }

        if (storeContext != null) {
            storeContext.delete();
        }

        vmContext.delete();
    }

    public void registerModuleFromFile(String modName, String filePath) {
        nativeRegisterModuleFromFile(vmContext.getPointer(), modName, filePath);
    }

    private native void nativeRegisterModuleFromFile(long vmContextPointer, String modName, String filePath);

    public void registerModuleFromBuffer(String moduleName, byte[] buffer) {
        nativeRegisterModuleFromBuffer(vmContext.getPointer(), moduleName, buffer);
    }

    private native void nativeRegisterModuleFromBuffer(long vmContextPointer, String moduleName, byte[] buffer);

    public void registerModuleFromImport(ImportObjectContext importObjectContext) {
        nativeRegisterModuleFromImport(vmContext.getPointer(), importObjectContext.getPointer());
    }

    private native void nativeRegisterModuleFromImport(long vmContextPointer, long importObjectPointer);

    public void registerModuleFromASTModule(String moduleName, ASTModuleContext astModuleContext) {
        nativeRegisterModuleFromASTModule(vmContext.getPointer(), moduleName, astModuleContext.getPointer());
    }

    private native void nativeRegisterModuleFromASTModule(long vmContextPointer, String moduleName, long astmContextPointer);

    public void executeRegistered(String modName, String funcName, List<WasmEdgeValue> params,
                                  List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);
        nativeExecuteRegistered(vmContext.getPointer(), modName, funcName, paramsArray, paramTypes, returnsArray, returnTypes);
    }

    private native void nativeExecuteRegistered(long vmContextPointer, String modName, String funcName, WasmEdgeValue[] params,
                                          int[] paramTypes, WasmEdgeValue[] returns, int[] returnTypes);

    private native int nativeGetFunctionListLength(long vmContextPointer);
    private native int nativeGetFunctionList(long vmContextPointer, long[] jPointersArray, Object[] jNamesArray, int bufferLen);

    public List<FunctionTypeContext> getFunctionList() {
        final int funcListLen = nativeGetFunctionListLength(vmContext.getPointer());
        final long[] jPointersArray = new long[funcListLen];
        final String[] jNamesArray = new String[funcListLen];

        final int actualFuncListLen = nativeGetFunctionList(vmContext.getPointer(), jPointersArray, jNamesArray, funcListLen);

        List<FunctionTypeContext> funcList = new ArrayList<>(actualFuncListLen);
        for (int i = 0; i < actualFuncListLen; i++) {
            funcList.add(new FunctionTypeContext(jPointersArray[i], jNamesArray[i]));
        }

        return funcList;
    }

    public FunctionTypeContext getFunctionType(String funcName) {
        return new FunctionTypeContext(nativeGetFunctionType(vmContext.getPointer(), funcName), funcName);
    }

    private native long nativeGetFunctionType(long vmContextPointer, String funcName);

    public ImportObjectContext getImportModuleContext(HostRegistration reg) {
        return new ImportObjectContext(nativeGetImportModuleContext(vmContext.getPointer(), reg.getVal()));
    }

    private native long nativeGetImportModuleContext(long vmContextPointer, int reg);


    public StoreContext getStoreContext() {
        return new StoreContext(nativeGetStoreContext(vmContext.getPointer()));
    }

    private native long nativeGetStoreContext(long vmContextPointer);

    public StatisticsContext getStatisticsContext() {
        return new StatisticsContext(nativeGetStatisticsContext(vmContext.getPointer()));
    }

    private native long nativeGetStatisticsContext(long vmContextPointer);

    public FunctionTypeContext getFunctionTypeRegistered(String moduleName,  String funcName) {
        return new FunctionTypeContext(nativeGetFunctionTypeRegistered(vmContext.getPointer(), moduleName, funcName), funcName);
    }

    private native long nativeGetFunctionTypeRegistered(long vmContextPointer, String moduleName, String funcName);
}
