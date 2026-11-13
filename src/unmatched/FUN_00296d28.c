/* Reads a Sofdec handle's playback time as a count/unit pair; an invalid handle, a failed read or a negative count all report 0/1. */
extern int FUN_002968c0(void *sfd);
extern void mwsfd_Error(const char *msg);
extern int FUN_002ae7b0(int stream, int *count, int *unit);
extern void FUN_00294ef8(int code);
extern char DAT_004f3d80[]; /* "E1122603 mwSfdGetTime; handle is invalid." */
extern char DAT_004f3db0[]; /* "E2006 mwSfdGetTime; can't get time" */

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
} Sfd296d28;

void FUN_00296d28(Sfd296d28 *sfd, int *count, int *unit) {
    if (FUN_002968c0(sfd) == 0) {
        mwsfd_Error(DAT_004f3d80);
        *count = 0;
        *unit = 1;
        return;
    }
    if (FUN_002ae7b0(sfd->stream, count, unit) != 0) {
        FUN_00294ef8(-309);
        mwsfd_Error(DAT_004f3db0);
        *count = 0;
        *unit = 1;
    }
    if (*count < 0) {
        *count = 0;
        *unit = 1;
    }
}
