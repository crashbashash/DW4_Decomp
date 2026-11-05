/* 0x002abe98 — FUN_002abe98 (88 bytes). Stops a handle: reports error 0xFF000133 if FUN_002a0dd8 refuses, otherwise runs FUN_002abef0 and sets the flag at +68. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0dd8(void *handle);
int FUN_002a0bb8(void *obj, int code);
int FUN_002abef0(void *handle);

struct Handle {
    char pad0[68];
    int stopped; /* +68 */
};

/* matching construct: implicit-int return (declared int, no value returned) — epilogue order */
int FUN_002abe98(struct Handle *handle) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF000133);
        return;
    }
    FUN_002abef0(handle);
    handle->stopped = 1;
}
