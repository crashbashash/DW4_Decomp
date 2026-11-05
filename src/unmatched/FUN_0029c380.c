/* 0x0029c380 — FUN_0029c380 (24 bytes). Forwards the handle and its word at +8200 to FUN_0029ea88. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[8200];
    int f8200;
} SfdHandle;

extern int FUN_0029ea88(SfdHandle *handle, int index);

void FUN_0029c380(SfdHandle *handle) {
    FUN_0029ea88(handle, handle->f8200);
}
