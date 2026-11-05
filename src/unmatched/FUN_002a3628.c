/* 0x002a3628 — FUN_002a3628 (220 bytes). Initialisation: hangs if FUN_002a3708 fails, maps a FUN_00290bd0 failure to error 0xFF000F13/0xFF000F01, else clears three tables. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002a96f0(void);
extern int FUN_002a3708(void);
extern int FUN_00290bd0(int a, void *b);
extern int FUN_002a0bb8(void *handle, int code);
extern void *memset(void *dst, int value, unsigned int size);
extern char DAT_00581570[];
extern char DAT_005855b0[];
extern char DAT_005855d8[];
extern char DAT_005855e0[];
extern int DAT_004beb08;

int FUN_002a3628(void) {
    int result;

    FUN_002a96f0();
    if (FUN_002a3708() != 0) {
        /* The EE short-loop workaround pads this empty loop with nops. */
        for (;;) {
        }
    }
    result = FUN_00290bd0(8, DAT_00581570);
    if (result != 0) {
        return FUN_002a0bb8(0, (result == (int)0xFF03FF05) ? 0xFF000F13 : 0xFF000F01);
    }
    memset(DAT_005855b0, 0, 36);
    memset(DAT_005855d8, 0, 8);
    memset(DAT_005855e0, 0, 64);
    DAT_004beb08 = 0;
    return 0;
}
