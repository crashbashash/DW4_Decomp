/* 0x002a38f0 — FUN_002a38f0 (24 bytes). Forwards the handle and its word at +8132 to FUN_0029ea88. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[8132];
    int f8132;
} SfdHandle;

extern int FUN_0029ea88(SfdHandle *handle, int index);

void FUN_002a38f0(SfdHandle *handle) {
    FUN_0029ea88(handle, handle->f8132);
}
