/* 0x002965a8 — FUN_002965a8 (124 bytes). Selects a playback handle's audio channel (its error strings name it mwPlySetAudioCh) through FUN_002aa5b8 on the +64 stream, reporting an invalid handle or channel number. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern int FUN_002aa5b8(int stream, int ch);
extern char DAT_004f3af0[]; /* "E1122616 mwPlySetAudioCh: handle is invalid." */
extern char DAT_004f3b20[]; /* "E10911A mwPlySetAudioCh: Invalid ch no." */

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
} Ply2965a8;

void FUN_002965a8(Ply2965a8 *ply, int ch) {
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f3af0);
        return;
    }
    if (FUN_002aa5b8(ply->stream, ch) != 0) {
        FUN_0029a320(DAT_004f3b20);
        return; /* matching construct: manual — the explicit return makes this call a tail jump */
    }
}
