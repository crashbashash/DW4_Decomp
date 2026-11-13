/* Sets a playback limit time: parameter 54 = `value`
 * * 1000 through FUN_002967b8, rejecting an invalid handle. */
extern int FUN_002968c0(void *sfd);
extern void mwsfd_Error(const char *msg);
extern void FUN_002967b8(void *sfd, int param, int value);
extern char DAT_004f3c08[]; /* "E1122625: mwPlySetLimitTime: handle is invalid." */

void FUN_002968f0(void *sfd, int value) {
    if (FUN_002968c0(sfd) == 0) {
        mwsfd_Error(DAT_004f3c08);
        return;
    }
    FUN_002967b8(sfd, 54, value * 1000);
}
