package org.wasmedge;

import org.wasmedge.enums.HostRegistration;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.UUID;

public class WasmEdgeVM {
    public static final Map<String, HostFunction> funcMap = new HashMap<>();
    private static final Map<String, Object> externRefMap = new HashMap<>();
    private final ConfigureContext configureContext;
    private final StoreContext storeContext;
    private long pointer;


    public WasmEdgeVM(ConfigureContext configureContext, StoreContext storeContext) {
        this.configureContext = configureContext;
        this.storeContext = storeContext;
        nativeInit(configureContext.getPointer(), storeContext.getPointer());
    }

    private native void nativeInit(long configureContextPointer, long storeContextPointer);

    protected static void addExternRef(String key, Object val) {
        externRefMap.put(key, val);
    }

    protected static Object getExternRef(String key) {
        return externRefMap.get(key);
    }

    protected static String addHostFunc(HostFunction hostFunction) {
        String key = UUID.randomUUID().toString();
        funcMap.put(key, hostFunction);
        return key;
    }

    protected static HostFunction getHostFunc(String key) {
        return funcMap.get(key);
    }

    private native void runWasmFromFile(String file, String funcName, WasmEdgeValue[] params, int paramSize, int[] paramTypes,
                                        WasmEdgeValue[] returns, int returnSize, int[] returnTypes);

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

        runWasmFromFile(file, funcName, paramsArray, params.size(), paramTypes,
                returnsArray, returns.size(), returnTypes);
    }

    public void runWasmFromBuffer(byte[] buffer, String funcName, List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);

        runWasmFromBuffer(buffer, funcName, paramsArray, paramTypes, returnsArray, returnTypes);
    }

    private native void runWasmFromBuffer(byte[] buffer, String funcName, WasmEdgeValue[] params, int[] paramTypes, WasmEdgeValue[] returns, int[] returnTypes);


    public void runWasmFromASTModule(ASTModuleContext astModuleContext, String funcName, List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);

        nativeRunWasmFromASTModule(astModuleContext.getPointer(), funcName, paramsArray, paramTypes, returnsArray, returnTypes);
    }

    private native void nativeRunWasmFromASTModule(long astmContextPointer, String funcName, WasmEdgeValue[] params, int[] paramTypes,
                                                   WasmEdgeValue[] returns, int[] returnTypes);

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

    public native void loadWasmFromFile(String filePath);

    // Not yet implemented in the JNI layer
//    public native void loadWasmFromBuffer(byte[] buffer);
//
//    public native void loadWasmFromASTModule(ASTModuleContext astModuleContext);

    public native void validate();

    public native void instantiate();

    public void execute(String funcName, List<WasmEdgeValue> params, List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);

        execute(funcName, paramsArray, params.size(), paramTypes, returnsArray, returns.size(), returnTypes);
    }

    public native void execute(String funcName, WasmEdgeValue[] params, int paramSize,  int[] paramTypes,
                               WasmEdgeValue[] returns, int returnSize, int[] returnTypes);

    // Also cleans up ConfigureContext & StoreContext
    public void destroy() {
        if (configureContext != null) {
            configureContext.delete();
        }

        if (storeContext != null) {
            storeContext.delete();
        }
        delete();
        this.pointer = 0;
    }

    public native void registerModuleFromFile(String modName, String filePath);

    public native void registerModuleFromBuffer(String moduleName, byte[] buffer);

    public native void registerModuleFromImport(ImportObjectContext importObjectContext);

    public void registerModuleFromASTModule(String moduleName, ASTModuleContext astModuleContext) {
        nativeRegisterModuleFromASTModule(moduleName, astModuleContext.getPointer());
    }

    private native void nativeRegisterModuleFromASTModule(String moduleName, long astmContextPointer);

    public void executeRegistered(String modName, String funcName, List<WasmEdgeValue> params,
                                  List<WasmEdgeValue> returns) {
        WasmEdgeValue[] paramsArray = valueListToArray(params);
        int[] paramTypes = getValueTypeArray(params);

        WasmEdgeValue[] returnsArray = valueListToArray(returns);
        int[] returnTypes = getValueTypeArray(returns);
        executeRegistered(modName, funcName, paramsArray, paramTypes, returnsArray, returnTypes);
    }

    private native void executeRegistered(String modName, String funcName, WasmEdgeValue[] params,
                                          int[] paramTypes, WasmEdgeValue[] returns, int[] returnTypes);

    private native int nativeGetFunctionListLength();
    private native int nativeGetFunctionList(long[] jPointersArray, Object[] jNamesArray, int bufferLen);

    public List<FunctionTypeContext> getFunctionList() {
        final int funcListLen = nativeGetFunctionListLength();
        final long[] jPointersArray = new long[funcListLen];
        final String[] jNamesArray = new String[funcListLen];

        final int actualFuncListLen = nativeGetFunctionList(jPointersArray, jNamesArray, funcListLen);

        List<FunctionTypeContext> funcList = new ArrayList<>(actualFuncListLen);
        for (int i = 0; i < actualFuncListLen; i++) {
            funcList.add(new FunctionTypeContext(jPointersArray[i], jNamesArray[i]));
        }

        return funcList;
    }

    public FunctionTypeContext getFunctionType(String funcName) {
        return new FunctionTypeContext(nativeGetFunctionType(funcName), funcName);
    }

    private native long nativeGetFunctionType(String funcName);

    public ImportObjectContext getImportModuleContext(HostRegistration reg) {
        return nativeGetImportModuleContext(reg.getVal());
    }

    private native ImportObjectContext nativeGetImportModuleContext(int reg);


    public StoreContext getStoreContext() {
        return new StoreContext(nativeGetStoreContext());
    }

    private native long nativeGetStoreContext();

    public StatisticsContext getStatisticsContext() {
        return new StatisticsContext(nativeGetStatisticsContext());
    }

    private native long nativeGetStatisticsContext();

    public FunctionTypeContext getFunctionTypeRegistered(String moduleName,  String funcName) {
        return new FunctionTypeContext(nativeGetFunctionTypeRegistered(moduleName, funcName), funcName);
    }

    private native long nativeGetFunctionTypeRegistered(String moduleName, String funcName);

    public native void cleanUp();

    private native void delete();
}
