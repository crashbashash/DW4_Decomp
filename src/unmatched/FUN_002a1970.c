/* 0x002a1970 — FUN_002a1970 (112 bytes). Runs FUN_002a1f28 on two values and, when it returns 1, invokes an optional callback with its two arguments; returns the status. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002a1f28(void *handle, int a, int b);

int FUN_002a1970(void *handle, void (*callback)(int, int), int callbackArg0, int callbackArg1,
                 int a, int b) {
    int status = FUN_002a1f28(handle, a, b);

    if (status == 1 && callback != 0) {
        callback(callbackArg0, callbackArg1);
    }
    return status;
}
