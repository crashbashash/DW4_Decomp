/* Part of mwPlyCreate: initialises the sub-block at +12 (FUN_00298260) and creates the additional-
 * information SJ from +404/+408 (FUN_0027bd48); on failure reports "can't create AddInfSJ" and
 * tears down with FUN_00293118. Returns the SJ or 0. */
int FUN_00298260(void *block);
int FUN_0027bd48(int buffer, int size, int flags);
void FUN_00293118(void *player);
void FUN_0029a320(const char *format, ...);

extern char DAT_004f43e0[]; /* "E201211 mwPlyCreate: can't create AddInfSJ" */

struct Player00298288 {
    char pad0[12];
    char block[404 - 12];  /* +12 */
    int addInfBuffer;      /* +404 */
    int addInfSize;        /* +408 */
};

int FUN_00298288(struct Player00298288 *player) {
    int sj;

    if (FUN_00298260(player->block) == 0) {
        return 0;
    }
    sj = FUN_0027bd48(player->addInfBuffer, player->addInfSize, 0);
    if (sj == 0) {
        FUN_0029a320(DAT_004f43e0);
        FUN_00293118(player);
        return 0;
    }
    return sj;
}
