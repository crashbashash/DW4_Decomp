/* 0x0027a688 — FUN_0027a688 (232 bytes). Closes a player object unless mode DAT_004b1dc8 is 1 with no pending count in DAT_004b1dc0: stops each channel handle (+16) with FUN_00272f90, sends command 9 with its id (+32) through FUN_00273820 and releases each channel stream (+8) with FUN_00279728. Always marks the object unused (byte 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Player_27a688 {
    signed char used;   /* 0x00 */
    char pad1[3];
    int channels;       /* 0x04 */
    int streams[2];     /* 0x08 */
    int handles[2];     /* 0x10 */
    char pad24[8];
    unsigned int id;    /* 0x20 */
} Player_27a688;

extern int DAT_004b1dc8;
extern int DAT_004b1dc0;
void FUN_00272f90(int handle);
void FUN_00279728(int stream);
int FUN_00273820(int command, unsigned int *args, int count, int a3, int t0);

void FUN_0027a688(Player_27a688 *player) {
    unsigned int args[4];
    int i;

    if (DAT_004b1dc8 != 1 || DAT_004b1dc0 > 0) {
        for (i = 0; i < player->channels; i++) {
            if (player->handles[i] != 0) {
                FUN_00272f90(player->handles[i]);
            }
        }
        args[0] = player->id;
        FUN_00273820(9, args, 1, 0, 0);
        for (i = 0; i < player->channels; i++) {
            if (player->streams[i] != 0) {
                FUN_00279728(player->streams[i]);
            }
        }
    }
    player->used = 0;
}

