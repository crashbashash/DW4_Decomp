/* 0x002abdb8 — FUN_002abdb8 (36 bytes). Clears +72/+76 and moves the handle to state 4 through FUN_002b02a0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdHandle {
    char pad0[72];
    int f72;                /* +72 */
    int f76;                /* +76 */
} SfdHandle;

extern void FUN_002b02a0(SfdHandle *handle, int state);

void FUN_002abdb8(SfdHandle *handle) {
    handle->f72 = 0;
    handle->f76 = 0;
    FUN_002b02a0(handle, 4);
}
