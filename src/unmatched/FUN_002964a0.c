/* 0x002964a0 — FUN_002964a0 (96 bytes). mwPlyGetNumSkipDec (named by its diagnostic string): for a valid player, returns status word 1 minus word 4 of the decoder status read by FUN_002add28; 0 for an invalid handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002968c0(void *player); /* non-zero for a valid player handle */
void *FUN_002963a8(void *player);
void FUN_002add28(void *decoder, int *status);
void FUN_0029a320(const char *format, ...);

extern char DAT_004f3a78[]; /* "E1122619: mwPlyGetNumSkipDec: handle is invalid." */

int FUN_002964a0(void *player) {
    int status[40];

    if (FUN_002968c0(player) == 0) {
        FUN_0029a320(DAT_004f3a78);
        return 0;
    }
    FUN_002add28(FUN_002963a8(player), status);
    return status[1] - status[4];
}
