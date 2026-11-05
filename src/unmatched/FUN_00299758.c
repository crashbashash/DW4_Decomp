/* 0x00299758 — FUN_00299758 (48 bytes). Reports three fixed buffer sizes (0x249E4, 0x9C40, 0x800) through the out pointers and returns their sum. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00299758(int *size0, int *size1, int *size2) {
    *size0 = 0x249E4;
    *size1 = 0x9C40;
    *size2 = 0x800;
    return *size0 + *size1 + *size2;
}
