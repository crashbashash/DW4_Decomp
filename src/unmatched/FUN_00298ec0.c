/* mwPlyEntryFname (named by its diagnostic strings): adds a file name to a valid player's file
 * list (+76, FUN_00277010) and counts the entries at +120; a failed entry sets state 4 and reports
 * the name. */
int FUN_002968c0(void *player); /* non-zero for a valid player handle */
int FUN_00277010(int list, const char *name);
void FUN_0029a320(const char *format, ...);

extern char DAT_004f45f8[]; /* "E1122633: mwPlyEntryFname: handle is invalid." */
extern char DAT_004f4628[]; /* "E10915B: mwPlyEntryFname: fname is NULL." */
extern char DAT_004f4658[]; /* "E204021: mwPlyEntryFname: Can't entry file'%s'" */

struct Player00298ec0 {
    int f0, f4;
    int state;             /* +8 */
    char pad12[76 - 12];
    int fileList;          /* +76 */
    char pad80[120 - 80];
    int entryCount;        /* +120 */
};

void FUN_00298ec0(struct Player00298ec0 *player, const char *name) {
    if (FUN_002968c0(player) == 0) {
        FUN_0029a320(DAT_004f45f8);
        return;
    }
    if (name == 0) {
        FUN_0029a320(DAT_004f4628);
        return;
    }
    if (FUN_00277010(player->fileList, name) < 0) {
        player->state = 4;
        FUN_0029a320(DAT_004f4658, name);
        return;
    }
    player->entryCount++;
}
