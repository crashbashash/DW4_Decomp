/* PS2RNA_GetStartSmpl by its message string: not implemented; reports "PS2RNA_GetStartSmpl: not
 * implemented" (FUN_002659a0) while the library is active (not mode 1 with no entries) and returns
 * 0. */
extern void FUN_002659a0(const char *format, ...);
extern int DAT_004b1dc0;
extern int DAT_004b1dc8;
extern const char PS2RNA_GetStartSmpl_not_implemented[];

int FUN_0027af28(void) {
    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0) {
        return 0;
    }
    FUN_002659a0(PS2RNA_GetStartSmpl_not_implemented);
    return 0;
}
