/* 0x00299310 — FUN_00299310 (136 bytes). Enters a file name with a range into the playback list (its error string names it mwPlyEntryFnameRange): forwards (a, 0, b, c) to FUN_00277038 on the +76 stream, rejecting an invalid handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern void FUN_00277038(int stream, int a, int zero, int b, int c);
extern char DAT_004f4850[]; /* "E407023: mwPlyEntryFnameRange: handle is invalid." */

typedef struct {
    char pad0[76];
    int f76;
} Ply299310;

void FUN_00299310(Ply299310 *ply, int a, int b, int c) {
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4850);
        return;
    }
    FUN_00277038(ply->f76, a, 0, b, c);
}
