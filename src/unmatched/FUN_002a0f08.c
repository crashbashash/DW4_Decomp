/* 0x002a0f08 — FUN_002a0f08 (28 bytes). Forwards the handle, its word at +7996 and the caller's value to FUN_0029dd80. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[7996];
    int f7996;
} SfdHandle;

extern int FUN_0029dd80(SfdHandle *handle, int index, int value);

void FUN_002a0f08(SfdHandle *handle, int value) {
    FUN_0029dd80(handle, handle->f7996, value);
}
