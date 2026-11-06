/* Returns the player's FUN_002a8878 count, one less when f2408 is 1, or 0 with error 0xFF000187
 * when FUN_002a0dd8 refuses the player. */
void FUN_002a0bb8();
int FUN_002a0dd8();
int FUN_002a8878();

struct Player2a8800 {
    char pad0[2408];
    int f2408;
};

int FUN_002a8800(struct Player2a8800 *player) {
    int refused;
    int count;

    refused = FUN_002a0dd8(player);
    if (refused != 0) {
        FUN_002a0bb8(0, 0xFF000187);
        return 0;
    }
    count = FUN_002a8878(player);
    if (player->f2408 == 1 && count > 0) {
        count--;
    }
    return count;
}
