/* 0x0029c398 — FUN_0029c398 (28 bytes). Forwards the handle, its word at +8200 and the caller's value to FUN_0029ea68. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[8200];
    int f8200;
} SfdHandle;

extern int FUN_0029ea68(SfdHandle *handle, int index, int value);

void FUN_0029c398(SfdHandle *handle, int value) {
    FUN_0029ea68(handle, handle->f8200, value);
}
