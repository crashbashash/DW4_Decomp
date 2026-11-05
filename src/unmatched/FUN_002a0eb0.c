/* 0x002a0eb0 — FUN_002a0eb0 (36 bytes). Sets stream +7996 to 1 through FUN_0029ea28 and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[7996];
    int f7996;              /* +7996 */
} SfdHandle;

extern int FUN_0029ea28(SfdHandle *handle, int index, int value);

int FUN_002a0eb0(SfdHandle *handle) {
    FUN_0029ea28(handle, handle->f7996, 1);
    return 0;
}
