/* 0x00299708 — FUN_00299708 (36 bytes). Returns the total of the three sizes FUN_00299758 reports, discarding the parts. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_00299758(int *size0, int *size1, int *size2);

int FUN_00299708(void) {
    int size0;
    int size1;
    int size2;

    return FUN_00299758(&size0, &size1, &size2);
}
