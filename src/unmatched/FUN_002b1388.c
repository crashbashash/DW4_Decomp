/* 0x002b1388 — FUN_002b1388 (28 bytes). Reports error 0xFF000601 for the handle through FUN_002a0bb8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a0bb8();

void FUN_002b1388(int handle) {
    FUN_002a0bb8(handle, 0xFF000601);
}
