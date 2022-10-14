package org.wasmedge;

public class Result {
    private boolean success;
    private boolean terminate;

    public static Result Ok = new Result(true, false);
    public static Result OkTerminate = new Result(true, true);
    public static Result Fail = new Result(false, false);

    public Result() {
        this(true, false);
    }

    public Result(boolean success) {
        this(success, false);
    }

    public Result(boolean success, boolean terminate) {
        this.success = success;
        this.terminate = terminate;
    }

    public boolean isSuccess() {
        return success;
    }

    public boolean isTerminate() {
        return terminate;
    }
}
