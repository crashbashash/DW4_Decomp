/* 0x00299068 — FUN_00299068 (168 bytes). Starts looped playback of a file (its error strings name it mwPlyStartFnameLp): rejects an invalid handle or a NULL name, otherwise opens the name (FUN_00295b68), resets the +76 stream, applies the +440 setting, enables looping and starts. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern void FUN_00295b68(void *ply, const char *fname);
extern void FUN_00277278(int stream);
extern void FUN_00298ec0(void *ply, int value);
extern void FUN_00299010(void *ply, int loop);
extern void FUN_00298f80(void *ply);
extern char DAT_004f46f0[]; /* "E1122630: mwPlyStartFnameLp: handle is invalid." */
extern char DAT_004f4720[]; /* "E10915A: mwPlyStartFnameLp: fname is NULL." */

typedef struct {
    char pad0[76];
    int f76;
    char pad80[360];
    int f440;
} Ply299068;

void FUN_00299068(Ply299068 *ply, const char *fname) {
    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f46f0);
        return;
    }
    if (fname == 0) {
        FUN_0029a320(DAT_004f4720);
        return;
    }
    FUN_00295b68(ply, fname);
    FUN_00277278(ply->f76);
    FUN_00298ec0(ply, ply->f440);
    FUN_00299010(ply, 1);
    FUN_00298f80(ply);
}
