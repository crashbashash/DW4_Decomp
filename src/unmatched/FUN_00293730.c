/* Sets a playback handle's frame-sync mode at +88,
 * rejecting an invalid handle. */
extern int FUN_002968c0(void *ply);
extern void mwsfd_Error(const char *msg);
extern char DAT_004f30a0[]; /* "E1122629: mwPlySetFrmSync: handle is invalid." */

typedef struct {
    char pad0[88];
    int frmSync;  /* 88 */
} Ply293730;

void FUN_00293730(Ply293730 *ply, int frmSync) {
    if (FUN_002968c0(ply) == 0) {
        mwsfd_Error(DAT_004f30a0);
        return;
    }
    ply->frmSync = frmSync;
}
