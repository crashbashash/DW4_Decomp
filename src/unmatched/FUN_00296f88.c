/* 0x00296f88 — FUN_00296f88 (100 bytes). Returns a Sofdec handle's output pan for a channel (its error string names it mwSfdGetOutPan): 0 for an invalid handle, otherwise FUN_00295e40's value. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002968c0(void *sfd);
extern void FUN_0029a320(const char *msg);
extern int FUN_00295e40(void *sfd, int channel);
extern char DAT_004f3e68[]; /* "E1122608 mwSfdGetOutPan: handle is invalid." */

int FUN_00296f88(void *sfd, int channel) {
    if (FUN_002968c0(sfd) == 0) {
        FUN_0029a320(DAT_004f3e68);
        return 0;
    }
    return FUN_00295e40(sfd, channel);
}
