/* 0x002a34d0 — FUN_002a34d0 (132 bytes). Validates the handle, then forwards four arguments to FUN_002a3558. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002a0dd8(void *handle);
extern int FUN_002a0bb8(void *handle, int code, int c, int d);
extern void FUN_002a3558(void *handle, int b);

void FUN_002a34d0(void *handle, int b, int c, int d) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF000185, c, d);
        return;
    }
    /* a2/a3 still hold c/d from the hoisted error-path setup; FUN_002a3558 may read them */
    FUN_002a3558(handle, b);
}
