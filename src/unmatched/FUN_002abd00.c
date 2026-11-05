/* 0x002abd00 — FUN_002abd00 (24 bytes). Calls FUN_002b02a0 on the handle with state 3. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002b02a0(void *handle, int state);

void FUN_002abd00(void *handle) {
    FUN_002b02a0(handle, 3);
}
