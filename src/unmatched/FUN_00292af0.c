/* 0x00292af0 — FUN_00292af0 (144 bytes). Resets a handle's SFD decoder (its error strings name it MWSFCRE_ResetSfdHn): stops it (FUN_002abe98, "SFD_Stop"), reinstalls the error callback FUN_00295010 (FUN_002a0c68, "SFD_SetErrFn") and reinitialises the handle; returns -1 on either failure. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002abe98(int sfd);
extern int FUN_002a0c68(int sfd, void (*errFn)(void), void *ctx);
extern void FUN_00295010(void);
extern void FUN_00294ef8(int code);
extern void FUN_002927f8(void *hn);
extern void FUN_0029a320(const char *msg);
extern char DAT_004f2d68[]; /* "E0203261: MWSFCRE_ResetSfdHn: SFD_Stop() failed." */
extern char DAT_004f2da0[]; /* "E0203262: MWSFCRE_ResetSfdHn: SFD_SetErrFn() failed." */

typedef struct {
    char pad0[64];
    int sfd;      /* 64: SFD decoder handle */
} Hn292af0;

int FUN_00292af0(Hn292af0 *hn) {
    int sfd = hn->sfd;

    if (FUN_002abe98(sfd) != 0) {
        FUN_0029a320(DAT_004f2d68);
        return -1;
    }
    if (FUN_002a0c68(sfd, FUN_00295010, hn) != 0) {
        FUN_00294ef8(-303);
        FUN_0029a320(DAT_004f2da0);
        return -1;
    }
    FUN_002927f8(hn);
    return 0;
}
