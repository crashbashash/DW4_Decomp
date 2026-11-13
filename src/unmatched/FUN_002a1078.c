/* Initialisation step: hangs if FUN_002a10e8 fails, reports 0xFF000D01 if FUN_0028d6e8 fails, else
 * clears DAT_004beb00. */
extern int FUN_002a10e8(void);
extern int FUN_0028d6e8(int a, void *b);
extern int sfd_ReportError(void *handle, int code);
extern char DAT_00580d60[];
extern int DAT_004beb00;

int FUN_002a1078(void) {
    int result;

    if (FUN_002a10e8() != 0) {
        /* The EE short-loop workaround pads this empty loop with nops. */
        for (;;) {
        }
    }
    result = FUN_0028d6e8(8, DAT_00580d60);
    if (result != 0) {
        return sfd_ReportError(0, 0xFF000D01);
    }
    DAT_004beb00 = 0;
    return result;
}
