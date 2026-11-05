/* 0x002aef78 — FUN_002aef78 (104 bytes). Checked entry point: validates the handle (error 0xFF00012A), then calls FUN_002aefe0 unless FUN_002adc40(handle, 71) reports 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002adc40();
int FUN_002aefe0();

/* FUN_002a0dd8(handle) records the handle in a global and returns -1 when it is null or its word at +72 is clear (asm/FUN_002a0dd8.s). */
int FUN_002aef78(int handle) {
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF00012A);
    }
    if (FUN_002adc40(handle, 71) == 1) {
        return 0;
    }
    FUN_002aefe0(handle);
    return 0;
}
