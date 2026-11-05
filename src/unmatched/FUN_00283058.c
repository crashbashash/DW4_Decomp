/* 0x00283058 — FUN_00283058 (52 bytes). Points 0x00573ea8 at the table 0x004f2800, clears the word returned
   by FUN_00283098 and calls FUN_002830a8(128). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int *FUN_00283098(void);
extern void FUN_002830a8(int size);
extern int DAT_004f2800[];
extern int *volatile DAT_00573ea8;

void FUN_00283058(void) {
    DAT_00573ea8 = DAT_004f2800;
    *FUN_00283098() = 0;
    FUN_002830a8(128);
}
