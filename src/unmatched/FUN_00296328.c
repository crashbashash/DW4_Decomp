/* Switches a playback handle's audio on or off: sets
 * stream parameter 6 through FUN_002ad950, rejecting an invalid handle. */
extern int FUN_002968c0(void *ply);
extern void mwsfd_Error(const char *msg);
extern void FUN_002ad950(int stream, int param, int value);
extern char DAT_004f39b8[]; /* "E1122617 mwPlySetAudioSw: handle is invalid." */

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
} Ply296328;

void FUN_00296328(Ply296328 *ply, int sw) {
    if (FUN_002968c0(ply) == 0) {
        mwsfd_Error(DAT_004f39b8);
        return;
    }
    FUN_002ad950(ply->stream, 6, sw);
}
