/* 0x0029c368 — FUN_0029c368 (24 bytes). Forwards the handle and its word at +8196 to FUN_0029ea88. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle_29c368 {
    char pad0[8196];
    int f8196;
} SfdHandle_29c368;

extern int FUN_0029ea88(SfdHandle_29c368 *handle, int index);

void FUN_0029c368(SfdHandle_29c368 *handle) {
    FUN_0029ea88(handle, handle->f8196);
}
