/* 0x0029d1b8 — FUN_0029d1b8 (108 bytes). Sets flag 7 through FUN_002b0388 once stream +8468 reports 1 and flag 7 is not already 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[8468];
    int f8468;              /* +8468 */
} SfdHandle;

extern int FUN_002b03a0(SfdHandle *handle, int flag);
extern int FUN_0029ea48(SfdHandle *handle, int index);
extern int FUN_002b0388(SfdHandle *handle, int flag, int value);

void FUN_0029d1b8(SfdHandle *handle) {
    if (FUN_002b03a0(handle, 7) != 1 && FUN_0029ea48(handle, handle->f8468) == 1) {
        FUN_002b0388(handle, 7, 1);
    }
}
