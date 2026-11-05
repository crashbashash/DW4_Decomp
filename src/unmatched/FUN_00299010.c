/* 0x00299010 — FUN_00299010 (88 bytes). Sets a playback handle's loop flag on its +76 stream through FUN_00277768 (its error string names it mwPlySetLpFlg), rejecting an invalid handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern void FUN_00277768(int stream, int loop);
extern char DAT_004f46c0[]; /* "E1122641: mwPlySetLpFlg: handle is invalid." */

typedef struct {
    char pad0[76];
    int f76;
} Ply299010;

void FUN_00299010(Ply299010 *ply, int loop) {
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f46c0);
        return;
    }
    FUN_00277768(ply->f76, loop);
}
