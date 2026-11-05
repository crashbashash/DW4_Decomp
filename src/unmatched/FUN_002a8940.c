/* 0x002a8940 — FUN_002a8940 (84 bytes). Validates the handle and reports whether FUN_002a8998 finds a current entry. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002a0dd8(void *handle);
extern int FUN_002a0bb8(void *handle, int code);
extern void *FUN_002a8998(void *handle);

int FUN_002a8940(void *handle) {
    if (FUN_002a0dd8(handle) != 0) {
        FUN_002a0bb8(0, 0xFF000183);
        return 0;
    }
    return FUN_002a8998(handle) != 0;
}
