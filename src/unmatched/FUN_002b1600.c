/* 0x002b1600 — FUN_002b1600 (28 bytes). Reports error 0xFF000701 for the handle through FUN_002a0bb8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();

void FUN_002b1600(int handle) {
    FUN_002a0bb8(handle, 0xFF000701);
}
