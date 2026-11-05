/* 0x00299730 — FUN_00299730 (36 bytes). Returns the total of the three sizes FUN_00299788 reports, discarding the parts. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_00299788(int *size0, int *size1, int *size2);

int FUN_00299730(void) {
    int size0;
    int size1;
    int size2;

    return FUN_00299788(&size0, &size1, &size2);
}
