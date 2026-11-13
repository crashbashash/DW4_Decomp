/* Closes a player object unless mode ps2rna_setup_voice is 1 with no pending count in ps2rna_nvoice:
 * stops each channel handle (+16) with FUN_00272f90, sends command 9 with its id (+32) through
 * DTX_CallUrpc and releases each channel stream (+8) with FUN_00279728. Always marks the object
 * unused (byte 0). */
typedef struct Player_27a688 {
    signed char used;   /* 0x00 */
    char pad1[3];
    int channels;       /* 0x04 */
    int streams[2];     /* 0x08 */
    int handles[2];     /* 0x10 */
    char pad24[8];
    unsigned int id;    /* 0x20 */
} Player_27a688;

extern int ps2rna_setup_voice;
extern int ps2rna_nvoice;
void FUN_00272f90(int handle);
void FUN_00279728(int stream);
int DTX_CallUrpc(int command, unsigned int *args, int count, int a3, int t0);

void FUN_0027a688(Player_27a688 *player) {
    unsigned int args[4];
    int i;

    if (ps2rna_setup_voice != 1 || ps2rna_nvoice > 0) {
        for (i = 0; i < player->channels; i++) {
            if (player->handles[i] != 0) {
                FUN_00272f90(player->handles[i]);
            }
        }
        args[0] = player->id;
        DTX_CallUrpc(9, args, 1, 0, 0);
        for (i = 0; i < player->channels; i++) {
            if (player->streams[i] != 0) {
                FUN_00279728(player->streams[i]);
            }
        }
    }
    player->used = 0;
}

