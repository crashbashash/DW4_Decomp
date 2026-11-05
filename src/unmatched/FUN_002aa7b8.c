/* 0x002aa7b8 — FUN_002aa7b8 (84 bytes). Validates the handle, then calls FUN_002aa868; returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002a0dd8(void *handle);
extern int FUN_002a0bb8(void *handle, int code);
extern void FUN_002aa868(void *handle);

int FUN_002aa7b8(void *handle) {
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000138);
    }
    FUN_002aa868(handle);
    return 0;
}
