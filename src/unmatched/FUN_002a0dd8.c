/* 0x002a0dd8 — FUN_002a0dd8 (32 bytes). Remembers the handle as the current one and returns 0 when it is live (+72 nonzero), else -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[72];
    int f72;                /* +72 */
} SfdHandle;

extern SfdHandle *DAT_004be8d0;

int FUN_002a0dd8(SfdHandle *handle) {
    DAT_004be8d0 = handle;
    if (handle == 0) {
        return -1;
    }
    return (handle->f72 != 0) ? 0 : -1;
}
