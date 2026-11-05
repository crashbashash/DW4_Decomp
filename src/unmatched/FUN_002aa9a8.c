/* 0x002aa9a8 — FUN_002aa9a8 (24 bytes). Calls FUN_002b02a0 on the handle with state 2. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002b02a0(void *handle, int state);

void FUN_002aa9a8(void *handle) {
    FUN_002b02a0(handle, 2);
}
