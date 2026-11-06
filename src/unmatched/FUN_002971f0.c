/* mwPlyGetPlyInf (named by its diagnostic string): fills a five-word playback statistics block for
 * a valid player: FUN_00296438, FUN_002964a0 (skipped decodes), FUN_00294308, FUN_002970e8 and
 * decoder status word 8 from FUN_002add28. */
int FUN_002968c0(void *player); /* non-zero for a valid player handle */
void *FUN_002963a8(void *player);
void FUN_002add28(void *decoder, int *status);
int FUN_00296438(void *player);
int FUN_002964a0(void *player);
int FUN_00294308(void *player);
int FUN_002970e8(void *player);
void FUN_0029a320(const char *format, ...);

extern char DAT_004f3f38[]; /* "E202191: mwPlyGetPlyInf: handle is invalid." */

struct Stats002971f0 {
    int f0, f4, f8, f12, f16;
};

void FUN_002971f0(void *player, struct Stats002971f0 *stats) {
    int status[40];

    if (FUN_002968c0(player) == 0) {
        FUN_0029a320(DAT_004f3f38);
        return;
    }
    FUN_002add28(FUN_002963a8(player), status);
    stats->f0 = FUN_00296438(player);
    stats->f4 = FUN_002964a0(player);
    stats->f8 = FUN_00294308(player);
    stats->f12 = FUN_002970e8(player);
    stats->f16 = status[8];
}
