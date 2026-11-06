/* MWSFD_MakeTblZ32 (named by its diagnostic strings): for a valid player and a fetched frame,
 * builds the conversion parameters (FUN_00297838) and makes the Z32 table with FUN_002b3708. */
int FUN_002968c0(void *player); /* non-zero for a valid player handle */
void *FUN_00297810(void *player);
void FUN_00297838(void *player, int *frame, void *params);
void FUN_002b3708(void *decoder, void *params);
void FUN_0029a320(const char *format, ...);

extern char DAT_004f44c8[]; /* "E202285: MWSFD_MakeTblZ32: handle is invalid." */
extern char DAT_004f44f8[]; /* "E202286: MWSFD_MakeTblZ32: getfrm is failed." */

struct Params00298a30 {
    int word[36];
};

void FUN_00298a30(void *player, int *frame) {
    struct Params00298a30 params;
    void *decoder;

    if (FUN_002968c0(player) == 0) {
        FUN_0029a320(DAT_004f44c8);
        return;
    }
    if (*frame == 0) {
        FUN_0029a320(DAT_004f44f8);
        return;
    }
    decoder = FUN_00297810(player);
    FUN_00297838(player, frame, &params);
    FUN_002b3708(decoder, &params);
}
