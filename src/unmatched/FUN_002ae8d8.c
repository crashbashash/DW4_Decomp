/* 0x002ae8d8 — FUN_002ae8d8 (116 bytes). Checked entry point: validates the handle with FUN_002a0dd8 (error 0xFF000127) and tail-calls FUN_002ae950 with the same arguments. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002ae950();

/* FUN_002a0dd8(handle) records the handle in a global and returns -1 when it is null or its word at +72 is clear (asm/FUN_002a0dd8.s). */
int FUN_002ae8d8(int handle, int arg1, int arg2) {
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000127);
    }
    return FUN_002ae950(handle, arg1, arg2);
}
