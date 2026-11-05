/* 0x0027b188 — FUN_0027b188 (68 bytes). PS2RNA_SetStmHdInfo by its message string: not implemented; reports "PS2RNA_SetStmHdInfo: not implemented"
   (FUN_002659a0) while the library is active (not mode 1 with no entries) and returns 0.
   Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_002659a0(const char *format, ...);
extern int DAT_004b1dc0;
extern int DAT_004b1dc8;
extern const char s_PS2RNA_SetStmHdInfo_not_implemented_004f1a30[];

int FUN_0027b188(void) {
    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0) {
        return 0;
    }
    FUN_002659a0(s_PS2RNA_SetStmHdInfo_not_implemented_004f1a30);
    return 0;
}
