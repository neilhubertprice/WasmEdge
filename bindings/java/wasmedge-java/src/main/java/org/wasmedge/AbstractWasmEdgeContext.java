package org.wasmedge;

public abstract class AbstractWasmEdgeContext {
    protected long pointer;

    protected AbstractWasmEdgeContext() {}

    protected AbstractWasmEdgeContext(final long pointer) {
        initialisePointer(pointer);
    }

    protected void initialisePointer(long pointer) {
        this.pointer = pointer;
        validatePointer(pointer);
    }

    private void validatePointer(final long pointer) {
        if (pointer == 0) {
            throw new WasmEdgeException(String.format("Null %s pointer", this.getClass().getSimpleName()));
        }
    }

    protected abstract void doDelete();

    public void delete() {
        doDelete();
        pointer = 0;
    }

    protected long getPointer() {
        return pointer;
    }
}
