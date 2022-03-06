package org.wasmedge;

import org.junit.Assert;
import org.junit.Ignore;
import org.junit.Test;
import org.wasmedge.enums.RefType;

import java.util.ArrayList;
import java.util.List;

public class TableTypeContextTest extends BaseTest {

    @Test
    @Ignore
    public void testCreation() {
        RefType refType = RefType.EXTERREF;
        WasmEdgeLimit limit = new WasmEdgeLimit(true, 1, 1000);
        TableTypeContext tableTypeContext = new TableTypeContext(refType, limit);

        Assert.assertEquals(tableTypeContext.getRefType(), refType);
        Assert.assertEquals(tableTypeContext.getLimit().isHasMax(), limit.isHasMax());
        Assert.assertEquals(tableTypeContext.getLimit().getMax(), limit.getMax());
        Assert.assertEquals(tableTypeContext.getLimit().getMin(), limit.getMin());
    }

    @Test
    @Ignore
    public void testRegisterWasmModule() {
        ConfigureContext configureContext = new ConfigureContext();
        StatisticsContext statisticsContext = new StatisticsContext();
        ASTModuleContext mod = loadMode(configureContext);
        ExecutorContext executorContext = new ExecutorContext(configureContext, statisticsContext);
        StoreContext storeContext = new StoreContext();
        String modName = "extern";
        executorContext.registerModule(storeContext, mod, modName);
    }

    @Test(expected = RuntimeException.class)
    @Ignore
    public void testRegisterWasmModuleNameConflict() {
        ConfigureContext configureContext = new ConfigureContext();
        StatisticsContext statisticsContext = new StatisticsContext();
        ASTModuleContext mod = loadMode(configureContext);
        ExecutorContext executorContext = new ExecutorContext(configureContext, statisticsContext);
        StoreContext storeContext = new StoreContext();
        String modName = "extern";
        executorContext.registerModule(storeContext, mod, modName);
        executorContext.registerModule(storeContext, mod, modName);
    }

    @Test
    @Ignore
    public void testInstantiateModule() {
        ConfigureContext configureContext = new ConfigureContext();
        StatisticsContext statisticsContext = new StatisticsContext();
        ASTModuleContext mod = loadMode(configureContext);
        ExecutorContext executorContext = new ExecutorContext(configureContext, statisticsContext);
        StoreContext storeContext = new StoreContext();
        executorContext.instantiate(storeContext, mod);
    }

    @Test(expected = RuntimeException.class)
    @Ignore
    public void testInstantiateModuleWithInvalidStore() {
        ConfigureContext configureContext = new ConfigureContext();
        StatisticsContext statisticsContext = new StatisticsContext();
        ASTModuleContext mod = loadMode(configureContext);
        ExecutorContext executorContext = new ExecutorContext(configureContext, statisticsContext);
        executorContext.instantiate(null, mod);
    }

    @Test(expected = RuntimeException.class)
    @Ignore
    public void testInstantiateModuleWithInvalidMod() {
        ConfigureContext configureContext = new ConfigureContext();
        StatisticsContext statisticsContext = new StatisticsContext();
        ExecutorContext executorContext = new ExecutorContext(configureContext, statisticsContext);
        StoreContext storeContext = new StoreContext();
        executorContext.instantiate(storeContext, null);
    }

    @Test
    @Ignore
    public void testOverrideInstantiatedModule() {
        ConfigureContext configureContext = new ConfigureContext();
        StatisticsContext statisticsContext = new StatisticsContext();
        ASTModuleContext mod = loadMode(configureContext);
        ExecutorContext executorContext = new ExecutorContext(configureContext, statisticsContext);
        StoreContext storeContext = new StoreContext();
        executorContext.instantiate(storeContext, mod);
        executorContext.instantiate(storeContext, mod);
    }

    @Test
    @Ignore
    public void testInvokeFunction() {
        String funcName = "func-mul-2";
        List<WasmEdgeValue> params = new ArrayList<>();
        params.add(new WasmEdgeI32Value(123));
        params.add(new WasmEdgeI32Value(456));
        List<WasmEdgeValue> returns = new ArrayList<>();
        params.add(new WasmEdgeI32Value());
        params.add(new WasmEdgeI32Value());
        ExecutorContext executorContext = new ExecutorContext(new ConfigureContext(), new StatisticsContext());
        executorContext.invoke(new StoreContext(), funcName, params, returns);
    }

    @Test
    @Ignore
    public void testInvokeFunctionTypeParamMismatch() {
        String funcName = "func-mul-2";
        List<WasmEdgeValue> params = new ArrayList<>();
        params.add(new WasmEdgeI32Value(123));
        List<WasmEdgeValue> returns = new ArrayList<>();
        params.add(new WasmEdgeI32Value());
        params.add(new WasmEdgeI32Value());
        ExecutorContext executorContext = new ExecutorContext(new ConfigureContext(), new StatisticsContext());
        executorContext.invoke(new StoreContext(), funcName, params, returns);
    }

    @Test
    @Ignore
    public void testInvokeFunctionNullParam() {
        String funcName = "func-mul-2";
        List<WasmEdgeValue> returns = new ArrayList<>();
        ExecutorContext executorContext = new ExecutorContext(new ConfigureContext(), new StatisticsContext());
        executorContext.invoke(new StoreContext(), funcName, null, returns);
    }

    @Test
    @Ignore
    public void testInvokeFunctionParamTypeMismatch() {
        String funcName = "func-mul-2";
        List<WasmEdgeValue> params = new ArrayList<>();
        params.add(new WasmEdgeI64Value(123));
        params.add(new WasmEdgeI32Value(456));
        List<WasmEdgeValue> returns = new ArrayList<>();
        params.add(new WasmEdgeI32Value());
        params.add(new WasmEdgeI32Value());
        ExecutorContext executorContext = new ExecutorContext(new ConfigureContext(), new StatisticsContext());
        executorContext.invoke(new StoreContext(), funcName, params, returns);
    }

    @Test
    @Ignore
    public void testInvokeFunctionParamTypeFunctionNotFound() {
        String funcName = "func-mul-3";
        List<WasmEdgeValue> params = new ArrayList<>();
        params.add(new WasmEdgeI64Value(123));
        params.add(new WasmEdgeI32Value(456));
        List<WasmEdgeValue> returns = new ArrayList<>();
        params.add(new WasmEdgeI32Value());
        params.add(new WasmEdgeI32Value());
        ExecutorContext executorContext = new ExecutorContext(new ConfigureContext(), new StatisticsContext());
        executorContext.invoke(new StoreContext(), funcName, params, returns);
    }

    @Test
    @Ignore
    public void testCallHostFunction() {
        Assert.fail();
    }

    @Test
    @Ignore
    public void testRegisteredModule() {
        Assert.fail();
    }




}
