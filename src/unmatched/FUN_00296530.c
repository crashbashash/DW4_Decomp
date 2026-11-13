/* mwPlySetBpicSkip / mwPlySetPpicSkip (named by the shared diagnostic): sets decoder parameter
 * `param` of a valid player's target (+64) to whether `mode` differs from 1. */
int FUN_002968c0(void *player); /* non-zero for a valid player handle */
void FUN_002ad950(int target, int param, int value);
void mwsfd_Error(const char *format, ...);

extern char DAT_004f3ab0[]; /* "E1122628: mwPlySetBpicSkip mwPlySetPpicSkip: handle is invalid." */

struct Player00296530 {
    char pad0[64];
    int target; /* +64 */
};

void FUN_00296530(struct Player00296530 *player, int mode, int param) {
    if (FUN_002968c0(player) == 0) {
        mwsfd_Error(DAT_004f3ab0);
        return;
    }
    FUN_002ad950(player->target, param, mode != 1);
}
