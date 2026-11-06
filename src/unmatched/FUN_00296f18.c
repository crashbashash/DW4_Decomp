/* mwSfdSetOutPan (named by its diagnostic string): forwards to FUN_00295e28 for a valid player
 * handle, else reports it invalid. */
int FUN_002968c0(void *player); /* non-zero for a valid player handle */
void FUN_00295e28(void *player, int channel, int pan);
void FUN_0029a320(const char *format, ...);

extern char DAT_004f3e38[]; /* "E1122607 mwSfdSetOutPan: handle is invalid." */

void FUN_00296f18(void *player, int channel, int pan) {
    if (FUN_002968c0(player) == 0) {
        FUN_0029a320(DAT_004f3e38);
        return;
    }
    FUN_00295e28(player, channel, pan);
}
