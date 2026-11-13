/* Returns a playback handle's skipped-display count at +136, or 0 for an invalid handle. */
extern int FUN_002968c0(void *ply);
extern void mwsfd_Error(const char *msg);
extern char DAT_004f3278[]; /* "E202231: mwPlyGetNumSkipDisp: handle is invalid." */

typedef struct {
    char pad0[136];
    int numSkipDisp;  /* 136 */
} Ply294308;

int FUN_00294308(Ply294308 *ply) {
    if (FUN_002968c0(ply) == 0) {
        mwsfd_Error(DAT_004f3278);
        return 0;
    }
    return ply->numSkipDisp;
}
