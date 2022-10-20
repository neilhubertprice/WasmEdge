package org.wasmedge;

public class WasmEdgeException extends RuntimeException {
    public WasmEdgeException(String message) {
        super(message);
    }

    public WasmEdgeException(String message, Throwable cause) {
        super(message, cause);
    }
}
