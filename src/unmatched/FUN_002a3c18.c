/* 0x002a3c18 — FUN_002a3c18 (28 bytes). Forwards the handle, its word at +8132 and the caller's value to FUN_0029ea68. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[8132];
    int f8132;
} SfdHandle;

extern int FUN_0029ea68(SfdHandle *handle, int index, int value);

void FUN_002a3c18(SfdHandle *handle, int value) {
    FUN_0029ea68(handle, handle->f8132, value);
}
