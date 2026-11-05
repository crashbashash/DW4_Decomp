/* 0x002a4120 — FUN_002a4120 (136 bytes). Reports error 0xFF000F1C when stream +8128 has less room than the minimum at +40; returns 0 otherwise. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[40];
    int f40;                /* +40 */
    char pad44[8084];
    int f8128;              /* +8128 */
} SfdHandle;

extern int FUN_0029e290(SfdHandle *handle, int index);
extern int FUN_0029eaa8(SfdHandle *handle, int index);
extern int FUN_002a0bb8(SfdHandle *handle, int code);

int FUN_002a4120(SfdHandle *handle) {
    int index = handle->f8128;
    int total = FUN_0029e290(handle, index);

    if (total - FUN_0029eaa8(handle, index) < handle->f40) {
        return FUN_002a0bb8(handle, 0xFF000F1C);
    }
    return 0;
}
