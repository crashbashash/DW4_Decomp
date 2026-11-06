/* Selects a playback handle's video channel through
 * FUN_002aa628 on the +64 stream, reporting an invalid handle or channel number. */
extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern int FUN_002aa628(int stream, int ch);
extern char DAT_004f3b78[]; /* "E2080601 mwPlySetVideoCh: handle is invalid." */
extern char DAT_004f3ba8[]; /* "E2080602 mwPlySetVideoCh: Invalid ch no." */

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
} Ply296698;

void FUN_00296698(Ply296698 *ply, int ch) {
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3b78);
        return;
    }
    if (FUN_002aa628(ply->stream, ch) != 0) {
        FUN_0029a320(DAT_004f3ba8);
        return; /* matching construct: manual — the explicit return makes this call a tail jump */
    }
}
