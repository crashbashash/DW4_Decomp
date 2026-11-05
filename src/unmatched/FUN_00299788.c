/* 0x00299788 — FUN_00299788 (52 bytes). Reports three fixed buffer sizes (0x6952C, 0x13C68, 0x2000) through the out pointers and returns their sum. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00299788(int *size0, int *size1, int *size2) {
    *size0 = 0x6952C;
    *size1 = 0x13C68;
    *size2 = 0x2000;
    return *size0 + *size1 + *size2;
}
