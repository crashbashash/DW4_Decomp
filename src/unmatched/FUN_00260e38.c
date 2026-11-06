/* Calls FUN_00260f08 with its four arguments plus the 64-byte-aligned buffer DAT_0049a800 and the
 * size 0x800. */
extern char DAT_0049a800[];
void FUN_00260f08(int a0, int a1, int a2, int a3, void *buffer, int size);

void FUN_00260e38(int a0, int a1, int a2, int a3) {
    FUN_00260f08(a0, a1, a2, a3, (void *)((int)DAT_0049a800 & ~0x3F), 0x800);
}
