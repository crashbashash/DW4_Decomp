/* 0x00260e60 — FUN_00260e60 (40 bytes). Calls FUN_00260f50 with its four arguments plus the 64-byte-aligned buffer DAT_0049a800 and the size 0x800. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern char DAT_0049a800[];
void FUN_00260f50(int a0, int a1, int a2, int a3, void *buffer, int size);

void FUN_00260e60(int a0, int a1, int a2, int a3) {
    FUN_00260f50(a0, a1, a2, a3, (void *)((int)DAT_0049a800 & ~0x3F), 0x800);
}
