/* 0x00298f80 — FUN_00298f80 (140 bytes). Starts seamless playback (its error string names it mwPlyStartSeamless): rejects an invalid handle, then FUN_002995e0(ply, 1), mwSfdStartSj (FUN_00295788) on the +468 joint, FUN_00295ab8, FUN_00277210 on +76, vtable slot +20 of the +464 joint, and FUN_00291d30. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SjObj SjObj;
typedef struct {
    char pad0[20];
    void (*fn20)(SjObj *sj); /* 20 */
} SjVtbl;
struct SjObj {
    SjVtbl *vtbl;
};

extern int FUN_002968c0(void *ply);
extern void FUN_0029a320(const char *msg);
extern void FUN_002995e0(void *ply, int arg);
extern void FUN_00295788(void *ply, int sj);
extern void FUN_00295ab8(void *ply);
extern void FUN_00277210(int stream);
extern void FUN_00291d30(void *ply);
extern char DAT_004f4688[]; /* "E1122634: mwPlyStartSeamless: handle is invalid." */

typedef struct {
    char pad0[76];
    int f76;
    char pad80[384];
    SjObj *sj;    /* 464 */
    int f468;
} Ply298f80;

void FUN_00298f80(Ply298f80 *ply) {
    SjObj *sj;

    if (FUN_002968c0(ply) == 0) {
        FUN_0029a320(DAT_004f4688);
        return;
    }
    FUN_002995e0(ply, 1);
    FUN_00295788(ply, ply->f468);
    FUN_00295ab8(ply);
    FUN_00277210(ply->f76);
    sj = ply->sj;
    if (sj != 0) {
        sj->vtbl->fn20(sj);
    }
    FUN_00291d30(ply);
}
