/* 0x002a2d00 — FUN_002a2d00 (28 bytes). Reports error code 0xFF000D0B for the handle through FUN_002a0bb8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002a0bb8(void *handle, int code);

void FUN_002a2d00(void *handle) {
    FUN_002a0bb8(handle, 0xFF000D0B);
}
